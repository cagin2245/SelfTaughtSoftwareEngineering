#include <iostream>
#include <string>

#include <chrono>
#include <sstream>
#include <iomanip>

#include "nlohmann/json.hpp"

using json = nlohmann::json;

class Student {
private:
   
    std::string name;
    int age;
    std::string studentID;
    std::string department;
    double gpa;
    static int counter; // Counter for generating unique student IDs
    
public:
    // Constructor
    Student() : name(""), age(0),  department(""), gpa(0.0) {}
    Student(const std::string& name, int age, const std::string& department, double gpa)
        : name(name), age(age), department(department), gpa(gpa) {
            this->studentID = generateStudentID(counter++);

        }

    
    // Getters
    std::string getName() const { return name; }
    int getAge() const { return age; }
    std::string getStudentID() const { return studentID; }
    std::string getDepartment() const { return department; }
    double getGPA() const { return gpa; }
    // Setters
    
    void setStudentID(const std::string& newID) { studentID = newID; }
    void setDepartment(const std::string& newDepartment) { department = newDepartment; }
    void setGPA(double newGPA) { gpa = newGPA; }
    // Print student details

    std::string generateStudentID(int counter) {
        auto now = std::chrono::system_clock::now();
        std::time_t time = std::chrono::system_clock::to_time_t(now);
        std::tm tm = *std::localtime(&time);

        std::stringstream oss;
        oss << std::put_time(&tm, "%Y%m") << std::setw(3) << std::setfill('0') << counter; // Format timestamp
        
        studentID = oss.str();
        return studentID;
    }
    
   

    void printDetails() const {
        std::cout << "Name: " << name << ", Age: " << age 
                << ", Student ID: " << studentID 
                << ", Department: " << department 
                << ", GPA: " << gpa << std::endl;
    }

    std::string toJson() const {
        return json{
            {"name", name},
            {"age", age},
            {"studentID", studentID},
            {"department", department},
            {"gpa", gpa}
        }.dump(); // Serialize to JSON string
    }

    static Student fromJson(const json& j) {
        Student s(
            j.at("name").get<std::string>(),
            j.at("age").get<int>(),
            j.at("department").get<std::string>(),
            j.at("gpa").get<double>()
        );
        s.setStudentID(j.at("studentID").get<std::string>());
        return s;
    }
    
    json toJsonObject() const {
        return json{
            {"name", name},
            {"age", age},
            {"studentID", studentID},
            {"department", department},
            {"gpa", gpa}
        };
    }
   
};