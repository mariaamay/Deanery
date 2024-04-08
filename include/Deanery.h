#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Group.h"
#include "Student.h"

class Group;

class Deanery
{
private:
	std::vector<Group*> groups;
public:
	Deanery() = default;
	void createStudentsFromFile(const std::string& filename);
	void createGroupsFromFile(const std::string& filename);
	void addRandomMarksToStudents();
	void getStatistics();
	void getStatistics(const std::string& groupName); //overloaded function to get statistics of the particular group
	void transferStudent(int id, const std::string& groupName);
	void expelStudent(int id);
	void saveData();
	void displayData();

	const std::vector<Group*>& getGroups() const;
	void setGroups(const std::vector<Group*>& groups);
};