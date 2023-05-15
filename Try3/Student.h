#pragma once
#include "Person.h"
class Student : public Person {
private:
    size_t course = 1;
	string major;
    size_t average_grade = 0;
public:
    Student() {}
    Student(string first_name, string last_name, string middle_name, size_t series, size_t number, size_t age, string major, size_t course) : 
        Person(first_name, last_name, middle_name, series, number, age), 
        major(major), 
        course(course) {}
    size_t get_course() const {
        return course;
    }
    string get_major() const {
        return major;
    }
    size_t get_average_grade() const {
        return average_grade;
    }

    void set_course(size_t new_course) {
        course = new_course;
    }
    void set_major(const string& new_major) {
        major = new_major;
    }
    void set_average_grade(size_t new_average_grade) {
        average_grade = new_average_grade;
    }
};

