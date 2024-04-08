#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Student.h"

class Student;

class Group {
private:
	std::string title;
	std::string speciality;
	std::vector<Student*> students;
	Student* head;

public:
	Group() = default;
	Group(const std::string& title, const std::string& speciality);
	void addStudent(const Student* student);
	void electHead();
	Student* getStudent(int id) const;
	Student* getStudent(const std::string& fio) const;
	double calculateAverageMarkGroup();
	void expelStudent(const Student* student);

	const std::string& getTitle() const;
	const std::string& getSpeciality() const;
	const std::vector<Student*>& getStudents() const;
	Student* getHead() const;

	void setTitle(const std::string& title);
	void setSpeciality(const std::string& speciality);
	void setStudents(const std::vector<Student*>& students);
	void setHead(Student* head);
};