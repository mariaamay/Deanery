#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Group.h"

class Group;

class Student {
private:
	int id;
	std::string fio;
	Group* group;
	std::vector<int> marks;

public:
	Student() = default;
	Student(int id, const std::string& fio);
	void enrollInGroup(Group* group);
	void addMark(int mark);
	double calculateAverageMark();

	int getId() const;
	const std::string& getFio() const;
	Group* getGroup() const;
	const std::vector<int>& getMarks() const;

	void setId(int id);
	void setFio(const std::string& fio);
	void setGroup(Group* group);
	void setMarks(const std::vector<int>& marks);
};