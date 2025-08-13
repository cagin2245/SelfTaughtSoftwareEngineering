#include <iostream>
#include <fstream>

using namespace std;

void readFile(const string& filename)
{
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();
}

int main() {
    string filename;
    cout << "Enter the filename to read: ";
    cin >> filename;

    readFile(filename);

    return 0;
}