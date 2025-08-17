#include <iostream>
#include "includes/studentManager.hpp"

int main()
{
    StudentManager db;

    Student s1("Alice", 20, "CS", 3.8);
    Student s2("Bob", 22, "Math", 3.5);

    db.addStudent(s1);
    db.addStudent(s2);

    for (auto &[k, v] : db)
    {
        std::cout << k << " = " << v << "\n";
    }

    Student found;
    if (db.findStudent("202508001", found))
    {
        std::cout << "Found student: " << found << std::endl;
    }
    else
    {
        std::cout << "Student not found." << std::endl;
    }

    db.removeStudent("202508001");
    db.saveToFile("students.json");
    db.loadFromFile("students.json");

    std::cout << "All students in the database:" << std::endl;
    for (const auto &[id, student] : db)
    {
        std::cout << "ID: " << id << ", Student: " << student << std::endl;
    }

    return 0;
}