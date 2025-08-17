#include <gtest/gtest.h>
#include "../includes/students.hpp"
#include "../includes/studentManager.hpp"
#include "../../hashmap/hashmap.hpp"

// ------------------ HashMap TESTS ------------------

TEST(HashMapTest, InsertAndFind) {
    HashMap<std::string, int> map;
    map.insert("one", 1);

    int value;
    EXPECT_TRUE(map.isValid("one", value));
    EXPECT_EQ(value, 1);
}

TEST(HashMapTest, DuplicateKeyUpdatesValue) {
    HashMap<std::string, int> map;
    map.insert("a", 10);
    map.insert("a", 20); // overwrite

    int value;
    EXPECT_TRUE(map.isValid("a", value));
    EXPECT_EQ(value, 20);
}

TEST(HashMapTest, RemoveElement) {
    HashMap<std::string, int> map;
    map.insert("a", 10);
    map.remove("a");

    int value;
    EXPECT_FALSE(map.isValid("a", value));
}

TEST(HashMapTest, IsEmptyWorks) {
    HashMap<std::string, int> map;
    EXPECT_TRUE(map.isEmpty());

    map.insert("a", 1);
    EXPECT_FALSE(map.isEmpty());
}

TEST(HashMapTest, IteratorTraversal) {
    HashMap<std::string, int> map;
    map.insert("x", 100);
    map.insert("y", 200);

    std::vector<std::string> keys;
    for (const auto& [k, v] : map) {
        keys.push_back(k);
    }

    EXPECT_EQ(keys.size(), 2);
}

TEST(HashMapTest, DerefEndThrows) {
    HashMap<std::string, int> map;
    auto it = map.end();
    EXPECT_THROW(*it, std::out_of_range);
}

// Stress test: rehash keeps elements valid
TEST(HashMapTest, RehashMaintainsData) {
    HashMap<std::string, int> map;
    for (int i = 0; i < 100; i++) {
        map.insert(std::to_string(i), i);
    }

    for (int i = 0; i < 100; i++) {
        int value;
        EXPECT_TRUE(map.isValid(std::to_string(i), value));
        EXPECT_EQ(value, i);
    }
}

// ------------------ Student TESTS ------------------

TEST(StudentTest, JsonRoundTrip) {
    Student s("Alice", 20, "CS", 3.8);
    auto j = s.toJson();
    Student s2 = Student::fromJson(j);

    EXPECT_EQ(s.getName(), s2.getName());
    EXPECT_EQ(s.getAge(), s2.getAge());
    EXPECT_EQ(s.getDepartment(), s2.getDepartment());
    EXPECT_EQ(s.getGPA(), s2.getGPA());
}

TEST(StudentTest, GettersAndSetters) {
    Student s("Bob", 22, "Math", 3.5);
    s.setDepartment("Physics");
    s.setGPA(3.9);

    EXPECT_EQ(s.getDepartment(), "Physics");
    EXPECT_DOUBLE_EQ(s.getGPA(), 3.9);
}

// ------------------ StudentManager TESTS ------------------

TEST(StudentManagerTest, AddAndFindStudent) {
    StudentManager manager;
    Student s("Alice", 20, "CS", 3.8);
    manager.addStudent(s);

    Student found;
    EXPECT_TRUE(manager.findStudent(s.getStudentID(), found));
    EXPECT_EQ(found.getName(), "Alice");
}

TEST(StudentManagerTest, RemoveStudent) {
    StudentManager manager;
    Student s("Bob", 22, "Math", 3.5);
    manager.addStudent(s);

    manager.removeStudent(s.getStudentID());
    Student found;
    EXPECT_FALSE(manager.findStudent(s.getStudentID(), found));
}

TEST(StudentManagerTest, SaveAndLoad) {
    StudentManager manager;
    Student s1("Alice", 20, "CS", 3.8);
    Student s2("Bob", 22, "Math", 3.5);
    manager.addStudent(s1);
    manager.addStudent(s2);

    manager.saveToFile("students_test.json");

    StudentManager loaded;
    loaded.loadFromFile("students_test.json");

    Student found1, found2;
    EXPECT_TRUE(loaded.findStudent(s1.getStudentID(), found1));
    EXPECT_TRUE(loaded.findStudent(s2.getStudentID(), found2));
    EXPECT_EQ(found1.getName(), "Alice");
    EXPECT_EQ(found2.getName(), "Bob");
}
