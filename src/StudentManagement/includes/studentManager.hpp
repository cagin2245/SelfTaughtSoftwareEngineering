#include <iostream>
#include <string>
#include "students.hpp"
#include "../../hashmap/hashmap.hpp"


class StudentManager {
private:
    HashMap<std::string, Student> studentMap; // HashMap to store students by ID
    
public:
    
    void addStudent(const Student& student);
    void removeStudent(const std::string& studentID);
    void printAll() const;
    bool findStudent(const std::string& studentID, Student& student) const;
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
    auto begin() { return studentMap.begin(); }
    auto end() { return studentMap.end(); }
        
    
};

inline std::ostream& operator<<(std::ostream& os, const Student& student) {
    os << "Name: " << student.getName() << ", Age: " << student.getAge()
       << ", Student ID: " << student.getStudentID() 
       << ", Department: " << student.getDepartment() 
       << ", GPA: " << student.getGPA();
    return os;
}
