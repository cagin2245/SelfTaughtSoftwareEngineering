#ifndef STUDENTS_HPP
#define STUDENTS_HPP

#include <iostream>
#include <string>

#include <chrono>
#include <sstream>
#include <iomanip>

#include "nlohmann/json.hpp"

using json = nlohmann::json;

class Student
{
private:
    std::string name;
    int age;
    std::string studentID;
    std::string department;
    double gpa;
    static int counter; // Counter for generating unique student IDs

public:
    // Constructor
    Student() : name(""), age(0), department(""), gpa(0.0) {}
    Student(std::string name, int age, std::string id, std::string dept, double gpa)
        : name(std::move(name)), age(age), studentID(std::move(id)), department(std::move(dept)), gpa(gpa) {}
    Student(const Student &) = default;                // copy ctor
    Student(Student &&) noexcept = default;            // move ctor
    Student &operator=(const Student &) = default;     // copy assign
    Student &operator=(Student &&) noexcept = default; // move assign
    ~Student() = default;

    // Getters
    std::string getName() const { return name; }
    int getAge() const { return age; }
    std::string getStudentID() const { return studentID; }
    std::string getDepartment() const { return department; }
    double getGPA() const { return gpa; }
    // Setters

    void setStudentID(const std::string &newID) { studentID = newID; }
    void setDepartment(const std::string &newDepartment) { department = newDepartment; }
    void setGPA(double newGPA) { gpa = newGPA; }

    friend std::ostream &operator<<(std::ostream &os, const Student &student)
    {
        os << "Name: " << student.name << ", Age: " << student.age
           << ", Student ID: " << student.studentID
           << ", Department: " << student.department
           << ", GPA: " << student.gpa;
        return os;
    }
    // Print student details

    std::string generateStudentID(int counter)
    {
        auto now = std::chrono::system_clock::now();
        std::time_t time = std::chrono::system_clock::to_time_t(now);
        std::tm tm = *std::localtime(&time);

        std::stringstream oss;
        oss << std::put_time(&tm, "%Y%m") << std::setw(3) << std::setfill('0') << counter; // Format timestamp

        studentID = oss.str();
        return studentID;
    }

    void printDetails() const
    {
        std::cout << "Name: " << name << ", Age: " << age
                  << ", Student ID: " << studentID
                  << ", Department: " << department
                  << ", GPA: " << gpa << std::endl;
    }

    json toJson() const
    {
        json j;
        j["name"] = name;
        j["age"] = age;
        j["department"] = department;
        j["gpa"] = gpa;
        j["studentID"] = studentID;
        return j;
    }

    static Student fromJson(const json &j)
    {
        try
        {
            Student s(
                j.at("name").get<std::string>(),
                j.at("age").get<int>(),
                j.at("department").get<std::string>(),
                j.at("gpa").get<double>());
            s.setStudentID(j.at("studentID").get<std::string>());
            return s;
        }
        catch (const json::exception &e)
        {
            std::cerr << "JSON parsing error: " << e.what() << std::endl;
            throw; // Re-throw the exception for further handling
        }
    }

    json toJsonObject() const
    {
        return json{
            {"name", name},
            {"age", age},
            {"studentID", studentID},
            {"department", department},
            {"gpa", gpa}};
    }
};

#endif // STUDENTS_HPP