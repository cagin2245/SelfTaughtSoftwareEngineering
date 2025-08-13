// minimal_json.cpp
#include <bits/stdc++.h>
using namespace std;

struct Json {
    using array_t = vector<Json>;
    using object_t = map<string, Json>;
    using value_t  = variant<nullptr_t, bool, double, string, array_t, object_t>;
    value_t v;

    // Type helpers
    bool is_null()   const { return holds_alternative<nullptr_t>(v); }
    bool is_bool()   const { return holds_alternative<bool>(v); }
    bool is_number() const { return holds_alternative<double>(v); }
    bool is_string() const { return holds_alternative<string>(v); }
    bool is_array()  const { return holds_alternative<array_t>(v); }
    bool is_object() const { return holds_alternative<object_t>(v); }

    const auto& as_array()  const { return get<array_t>(v); }
    const auto& as_object() const { return get<object_t>(v); }
    const auto& as_string() const { return get<string>(v); }
    double      as_number() const { return get<double>(v); }
    bool        as_bool()   const { return get<bool>(v); }
};

struct ParseError : runtime_error {
    size_t line, col;
    ParseError(const string& msg, size_t line_, size_t col_)
        : runtime_error(msg), line(line_), col(col_) {}
};

struct Parser {
    const string& s;
    size_t i = 0;
    size_t line = 1, col = 1;

    Parser(const string& s_) : s(s_) {}

    void advance() {
        if (i < s.size()) {
            if (s[i] == '\n') { line++; col = 1; }
            else col++;
            i++;
        }
    }
    char peek() const { return i < s.size() ? s[i] : '\0'; }
    bool eof()  const { return i >= s.size(); }

    [[noreturn]] void fail(const string& msg) const {
        throw ParseError("JSON parse error: " + msg, line, col);
    }

    void skip_ws() {
        while (!eof()) {
            char c = peek();
            if (c==' ' || c=='\t' || c=='\r' || c=='\n') advance();
            else break;
        }
    }

    void expect_char(char want) {
        if (peek() != want) {
            fail(string("expected '") + want + "' but found '" + peek() + "'");
        }
        advance();
    }

    Json parse() {
        skip_ws();
        Json val = parse_value();
        skip_ws();
        if (!eof()) fail("trailing characters after root value");
        return val;
    }

    Json parse_value() {
        skip_ws();
        char c = peek();
        if (c == '"') return Json{ parse_string() };
        if (c == '-' || isdigit((unsigned char)c)) return Json{ parse_number() };
        if (c == '{') return Json{ parse_object() };
        if (c == '[') return Json{ parse_array() };
        if (c == 't') { parse_literal("true");  return Json{ true };  }
        if (c == 'f') { parse_literal("false"); return Json{ false }; }
        if (c == 'n') { parse_literal("null");  return Json{ nullptr }; }
        if (c == '\0') fail("unexpected end of input");
        fail(string("unexpected character: '") + c + "'");
    }

    void parse_literal(const char* lit) {
        for (const char* p = lit; *p; ++p) {
            if (peek() != *p) fail(string("expected literal '") + lit + "'");
            advance();
        }
    }

    // Parses string and returns std::string
    string parse_string() {
        expect_char('"');
        string out;
        while (!eof()) {
            char c = peek();
            advance();
            if (c == '"') break; // end of string
            if (c == '\\') {
                if (eof()) fail("unfinished escape sequence");
                char e = peek(); advance();
                switch (e) {
                    case '"': out.push_back('"');  break;
                    case '\\': out.push_back('\\'); break;
                    case '/': out.push_back('/');   break;
                    case 'b': out.push_back('\b');  break;
                    case 'f': out.push_back('\f');  break;
                    case 'n': out.push_back('\n');  break;
                    case 'r': out.push_back('\r');  break;
                    case 't': out.push_back('\t');  break;
                    case 'u': {
                        // Basic \uXXXX (no surrogate handling for simplicity)
                        uint32_t code = 0;
                        for (int k=0;k<4;k++) {
                            if (eof()) fail("unfinished \\uXXXX");
                            char h = peek(); advance();
                            code <<= 4;
                            if      (h>='0' && h<='9') code |= (h - '0');
                            else if (h>='a' && h<='f') code |= (h - 'a' + 10);
                            else if (h>='A' && h<='F') code |= (h - 'A' + 10);
                            else fail("invalid hex in \\uXXXX");
                        }
                        // encode to UTF-8
                        if (code <= 0x7F) out.push_back(char(code));
                        else if (code <= 0x7FF) {
                            out.push_back(char(0xC0 | (code >> 6)));
                            out.push_back(char(0x80 | (code & 0x3F)));
                        } else if (code <= 0xFFFF) {
                            out.push_back(char(0xE0 | (code >> 12)));
                            out.push_back(char(0x80 | ((code >> 6) & 0x3F)));
                            out.push_back(char(0x80 | (code & 0x3F)));
                        } else {
                            // Not handling >0xFFFF via surrogate pairs in this minimal parser
                            fail("codepoint > 0xFFFF not supported in this minimal parser");
                        }
                        break;
                    }
                    default:
                        fail(string("invalid escape \\") + e);
                }
            } else {
                // disallow unescaped control chars
                if ((unsigned char)c <= 0x1F) fail("control character in string");
                out.push_back(c);
            }
        }
        return out;
    }

    // Parses number via strtod (locale-independent)
    double parse_number() {
        const char* begin = s.c_str() + i - 1; // we already consumed one char in parse_value? Not yet.
        // Fix: ensure begin is at current i, not i-1
        // We'll reposition: step back one since we haven't consumed current char yet.
        i--; col--; // move back to start of number
        begin = s.c_str() + i;

        char* endptr = nullptr;
        errno = 0;
        double val = strtod(begin, &endptr);
        if (begin == endptr) fail("invalid number");
        if (errno == ERANGE) {
            // still accept but warn; here we throw
            fail("number out of range");
        }
        // move parser index to endptr
        size_t consumed = static_cast<size_t>(endptr - s.c_str()) - i;
        for (size_t k=0; k<consumed; ++k) advance();
        return val;
    }

    Json::array_t parse_array() {
        expect_char('[');
        skip_ws();
        Json::array_t arr;
        if (peek() == ']') { advance(); return arr; }
        while (true) {
            arr.push_back(parse_value());
            skip_ws();
            if (peek() == ',') { advance(); skip_ws(); continue; }
            if (peek() == ']') { advance(); break; }
            fail("expected ',' or ']' in array");
        }
        return arr;
    }

    Json::object_t parse_object() {
        expect_char('{');
        skip_ws();
        Json::object_t obj;
        if (peek() == '}') { advance(); return obj; }
        while (true) {
            if (peek() != '"') fail("object key must be a string");
            string key = parse_string();
            skip_ws();
            expect_char(':');
            skip_ws();
            Json val = parse_value();
            obj.emplace(std::move(key), std::move(val));
            skip_ws();
            if (peek() == ',') { advance(); skip_ws(); continue; }
            if (peek() == '}') { advance(); break; }
            fail("expected ',' or '}' in object");
        }
        return obj;
    }
};

// Pretty printer
void dump_impl(const Json& j, ostream& os, int indent, int depth) {
    auto pad = [&](int d){ for(int k=0;k<d;k++) os.put(' '); };

    if (j.is_null()) { os << "null"; return; }
    if (j.is_bool()) { os << (j.as_bool() ? "true" : "false"); return; }
    if (j.is_number()) { 
        // Print without trailing .0 if possible
        double x = j.as_number();
        if (floor(x) == x && isfinite(x)) os << fixed << setprecision(0) << x;
        else os << setprecision(15) << x;
        return;
    }
    if (j.is_string()) {
        os << '"';
        for (char c: j.as_string()) {
            switch(c){
                case '"': os << "\\\""; break;
                case '\\': os << "\\\\"; break;
                case '\b': os << "\\b"; break;
                case '\f': os << "\\f"; break;
                case '\n': os << "\\n"; break;
                case '\r': os << "\\r"; break;
                case '\t': os << "\\t"; break;
                default:
                    if ((unsigned char)c <= 0x1F) {
                        os << "\\u" << hex << setw(4) << setfill('0') << (int)(unsigned char)c << dec << setfill(' ');
                    } else os << c;
            }
        }
        os << '"';
        return;
    }
    if (j.is_array()) {
        const auto& a = j.as_array();
        os << "[";
        if (!a.empty()) {
            os << "\n";
            for (size_t idx=0; idx<a.size(); ++idx) {
                pad(depth+indent);
                dump_impl(a[idx], os, indent, depth+indent);
                if (idx+1<a.size()) os << ",";
                os << "\n";
            }
            pad(depth);
        }
        os << "]";
        return;
    }
    if (j.is_object()) {
        const auto& o = j.as_object();
        os << "{";
        if (!o.empty()) {
            os << "\n";
            size_t cnt=0;
            for (auto& [k,v] : o) {
                pad(depth+indent);
                os << '"' << k << "\": ";
                dump_impl(v, os, indent, depth+indent);
                if (++cnt<o.size()) os << ",";
                os << "\n";
            }
            pad(depth);
        }
        os << "}";
        return;
    }
}

string dump(const Json& j, int indent=2) {
    ostringstream oss;
    dump_impl(j, oss, indent, 0);
    return oss.str();
}

// Small helper: read whole file
string read_file(const string& path) {
    ifstream ifs(path, ios::binary);
    if (!ifs) throw runtime_error("cannot open file: " + path);
    ostringstream oss;
    oss << ifs.rdbuf();
    return oss.str();
}

int main(int argc, char** argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    try {
        string input;
        if (argc >= 2) {
            input = read_file(argv[1]);
        } else {
            // read from stdin if no file path
            ostringstream oss;
            oss << cin.rdbuf();
            input = oss.str();
        }
        Parser p(input);
        Json root = p.parse();

        cout << dump(root, 2) << "\n";
        return 0;
    } catch (const ParseError& e) {
        cerr << "ParseError at line " << e.line << ", col " << e.col << ": " << e.what() << "\n";
        return 1;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}
