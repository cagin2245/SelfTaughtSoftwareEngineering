#include "includes/students.hpp"

#include "includes/nlohmann/json.hpp"

using json = nlohmann::json;

int Student::counter = 0;   // static member definition

void Student::printDetails() const {
    std::cout << "Name: " << name << ", Age: " << age 
              << ", Student ID: " << studentID 
              << ", Department: " << department 
              << ", GPA: " << gpa << std::endl;
}

std::string Student::toJson() const {
    return json{
        {"name", name},
        {"age", age},
        {"studentID", studentID},
        {"department", department},
        {"gpa", gpa}
    };
}

Student Student::fromJson(const std::string& jsonStr) {
    json j = json::parse(jsonStr);
    Student s(
        j.at("name").get<std::string>(),
        j.at("age").get<int>(),
        j.at("department").get<std::string>(),
        j.at("gpa").get<double>()
    );
    s.setStudentID(j.at("studentID").get<std::string>()); 
    return s;
}