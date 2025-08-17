#include <iostream>
#include "includes/studentManager.hpp"






int main() {
    StudentManager db;

    Student s1("Alice", 20, "CS", 3.8);
    Student s2("Bob", 22,  "Math", 3.5);

    db.addStudent(s1);
    db.addStudent(s2);

    db.printAll();
    db.saveToFile("students.json");
    
    Student found;
    if (db.findStudent("S001", found)) {
        found.printDetails();
    }

    return 0;
    
}