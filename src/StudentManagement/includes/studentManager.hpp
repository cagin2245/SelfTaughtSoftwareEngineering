#include <iostream>
#include <string>
#include "students.hpp"
#include "../../hashmap/hashmap.hpp"


class StudentManager {
private:
    HashMap<std::string, std::shared_ptr<Student>> studentMap; // HashMap to store students by ID
    
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

