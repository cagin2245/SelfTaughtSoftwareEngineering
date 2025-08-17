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
    for (const auto& bucket : studentMap.getTable()) {
        for (const auto& pair : bucket) {
            j["students"].push_back(pair.second.toJson());
        }
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
    std::string line;
    while (std::getline(file, line)) {
        json j = json::parse(line);
        Student student = Student::fromJson(j);
        studentMap.insert(student.getStudentID(), student); // Insert the student into the map
    }
    file.close();
}
