#pragma once
#include <string>
using namespace std;

class Passport {
private:
	size_t series, number;
public:
	Passport() {}
	Passport(size_t series, size_t number) : series(series), number(number) {}
	size_t get_series() {
		return this->series;
	}
	size_t get_number() {
		return this->number;
	}
	Passport* set_series(size_t series) {
		this->series = series;
		return this;
	}
	Passport* set_number(size_t number) {
		this->number = number;
		return this;
	}
};

class Person {
private:
	Passport passport;
	string first_name;
	string last_name;
	string middle_name;
	size_t age = 0;
public:
	Person() {}
	Person(string first_name, string last_name, string middle_name, size_t series, size_t number, size_t age) : 
		first_name(first_name), 
		last_name(last_name), 
		middle_name(middle_name), 
		passport(Passport(series, number)), 
		age(age) {}
	string get_first_name() const {
		return this->first_name;
	}
	string get_last_name() const {
		return this->last_name;
	}
	string get_middle_name() const {
		return this->middle_name;
	}
	size_t get_age() const {
		return this->age;
	}

	Person* set_first_name(string name) {
		this->first_name = name;
		return this;
	}
	Person* set_last_name(string name) {
		this->last_name = name;
		return this;
	}
	Person* set_middle_name(string name) {
		this->middle_name = name;
		return this;
	}
	Person* set_age(size_t age) {
		this->age = age;
		return this;
	}
};
