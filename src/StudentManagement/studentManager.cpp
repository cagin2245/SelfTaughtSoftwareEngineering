#include "includes/studentManager.hpp"
#include <fstream>
#include "includes/nlohmann/json.hpp"

using json = nlohmann::json;


void StudentManager::addStudent(const Student& student) {
    studentMap.insert(student.getStudentID(), student);
}
void StudentManager::removeStudent(const std::string& studentID) {
    studentMap.remove(studentID);
}
void StudentManager::printAll() const {
    studentMap.print();
}
bool StudentManager::findStudent(const std::string& studentID, Student& student) const {
    return studentMap.isValid(studentID, student);
}

void StudentManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open file for writing: " << filename << std::endl;
        return;
    }

    json j;
    for (const auto& [id, student] : studentMap) {
    j["students"].push_back(student.toJsonObject()); // <-- toJsonObject() returns a JSON object
        // or you can use student.toJson() if you want a string
        // j["students"].push_back(student.toJson());
    // toJson() method returns a JSON string representation of the student}
    }

    file << j.dump(4); // 4 = pretty print
}
void StudentManager::loadFromFile(const std::string& filename
) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open file for reading: " << filename << std::endl;
        return;
    }

    json j;
    file >> j;  // tüm JSON'u oku

    if (j.contains("students") && j["students"].is_array()) {
        for (const auto& item : j["students"]) {
            Student student = Student::fromJson(item); // burada item zaten object
            studentMap.insert(student.getStudentID(), student);
        }
    }
}