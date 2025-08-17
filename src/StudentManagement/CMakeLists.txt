cmake_minimum_required(VERSION 3.15)
project(StudentManagement)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(
    ${PROJECT_SOURCE_DIR}/includes
    ${PROJECT_SOURCE_DIR}/hashmap
)

# Source files
set(SOURCES
    main.cpp
    students.cpp
    studentManager.cpp
)

enable_testing()
add_executable(test_student tests/test_student.cpp StudentManager.cpp students.cpp)
target_link_libraries(test_student gtest gtest_main pthread)
add_test(NAME student_tests COMMAND test_student)


# Executable
add_executable(student_management ${SOURCES})