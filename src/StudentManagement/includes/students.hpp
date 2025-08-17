#include <iostream>
#include <string>

#include <chrono>
#include <sstream>
#include <iomanip>



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
    void printDetails() const;
    std::string toJson() const;
    static Student fromJson(const std::string& jsonStr);
    
   
};