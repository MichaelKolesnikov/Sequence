#pragma once
#include "Person.h"
class Educator : public Person {
private:
    string subject;
    string qualification;
public:
	Educator(string first_name, string last_name, string middle_name, size_t series, size_t number, size_t age, string subject, string qualification) :
		Person(first_name, last_name, middle_name, series, number, age),
		subject(subject),
		qualification(qualification) {}

	string get_subject() const {
		return subject;
	}

	string get_qualification() const {
		return qualification;
	}

	Educator* set_subject(string subject) {
		this->subject = subject;
		return this;
	}

	Educator* set_qualification(string qualification) {
		this->qualification = qualification;
		return this;
	}

};


