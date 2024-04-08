#include "Deanery.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>


void Deanery::createStudentsFromFile(const std::string& filename) {
	std::ifstream file(filename);

	if (!file.is_open()) {
		std::cerr << "Error opening file!" << std::endl;
		return;
	}
	else {
		std::string line;
		while (std::getline(file, line)) {
			std::istringstream iss(line);
			int id;
			std::string surname, name, patronymic, groupName;
			if (!(iss >> id >> surname >> name >> patronymic >> groupName)) {
				break;
			}
			Student* student = new Student(id, surname + " " + name + " " + patronymic);
			for (Group* group : groups) {
				if (groupName == group->getTitle()) {
					student->setGroup(group);
					group->addStudent(student);
				}
			}
			int mark;
			std::vector<int> marks;
			while (iss >> mark) {
				marks.push_back(mark);
			}
			student->setMarks(marks);
		}
	}
}

void Deanery::createGroupsFromFile(const std::string& filename) {
	std::ifstream file(filename);

	if (!file.is_open()) {
		std::cerr << "Error opening file!" << std::endl;
		return;
	}
	else {
		std::string line; 
		while (std::getline(file, line)) {
			std::istringstream iss(line);
			std::string title, speciality, surnameHead, nameHead, patronymicHead;
			if (!(iss >> title >> speciality >> surnameHead >> nameHead >> patronymicHead)) {
				break;
			}
			std::string fio = surnameHead + " " + nameHead + " " + patronymicHead;
			Student* student = new Student(0, fio);
			Group* group = new Group(title, speciality);
			group->setHead(student);
			groups.push_back(group);
		}
	}
	file.close();
}

void Deanery::addRandomMarksToStudents() {
	srand(time(0));
	for (Group* group : groups) {
		for (Student* student : group->getStudents()) {
			int mark = rand() % 11;
			student->addMark(mark);
		}
	}
}

void Deanery::getStatistics() {
	std::cout << "The number of groups: " << groups.size() << std::endl;
	for (Group* group : groups) {
		std::cout << "Group: " << group->getTitle() << std::endl;
		std::cout << "The number of students: " << group->getStudents().size() << std::endl;
		std::cout << "The average mark of the group: " << group->calculateAverageMarkGroup() << std::endl;
		std::cout << "The statictics of every student: " << std::endl;
		for (Student* student : group->getStudents()) {
			std::cout << student->getFio() << " : ";
			for (int mark : student->getMarks()) {
				std::cout << mark << " ";
			}
			std::cout << std::endl;
			std::cout << "The average mark: " << student->calculateAverageMark() << std::endl;
		}
		std::cout << std::endl;
	}
}

void Deanery::getStatistics(const std::string& groupName) {
	for (Group* group : groups) {
		if (group->getTitle() == groupName) {
			std::cout << "Group: " << group->getTitle() << std::endl;
			std::cout << "The number of students: " << group->getStudents().size() << std::endl;
			std::cout << "The average mark of the group: " << group->calculateAverageMarkGroup() << std::endl;
			std::cout << "The statictics of every student: " << std::endl;
			for (Student* student : group->getStudents()) {
				std::cout << student->getFio() << " : ";
				for (int mark : student->getMarks()) {
					std::cout << mark << " ";
				}
				std::cout << std::endl;
				std::cout << "The average mark: " << student->calculateAverageMark() << std::endl;
			}
		}
	}
}

void Deanery::transferStudent(int id, const std::string& groupName) {
	Student* studentToTransfer = nullptr;
	Group* newGroup = nullptr;

	for (Group* group : groups) {
		if (group->getTitle() == groupName) {
			newGroup = group;
			break;
		}
	}
	if (newGroup == nullptr) {
		std::cerr << "Error: invalid name of the group\n";
		return;
	}

	for (Group* group : groups) {
		if (group->getStudent(id) != nullptr) {
				studentToTransfer = group->getStudent(id);
				newGroup->addStudent(studentToTransfer);
				studentToTransfer->setGroup(newGroup);
				group->expelStudent(studentToTransfer);
				break;
		}
	}
	if (studentToTransfer == nullptr) {
		std::cerr << "Error: invalid ID\n";
		return;
	}
}

void Deanery::expelStudent(int id) {
	Student* studentToExpell = nullptr;
	Group* groupToExpellFrom = nullptr;

	for (Group* group : groups) {
		if (group->getStudent(id) != nullptr) {
			studentToExpell = group->getStudent(id);
			groupToExpellFrom = group;
			break;
		}
	}
	if (groupToExpellFrom == nullptr) {
		std::cerr << "Error: Student not found\n";
	}

	if (studentToExpell->calculateAverageMark() < 4.0) {
		groupToExpellFrom->expelStudent(studentToExpell);
	}
	else {
		std::cout << "Student has an average mark more than 4" << std::endl;
	}
}

void Deanery::saveData() {
	std::ofstream fileGroups("C:\\Users\\PC\\source\\repos\\Deanery\\bd\\groups.txt");
	std::ofstream fileStudents("C:\\Users\\PC\\source\\repos\\Deanery\\bd\\students.txt");

	if (!fileGroups.is_open() || !fileStudents.is_open()) {
		std::cerr << "Error opening file!" << std::endl;
		return;
	}

	for (Group* group : groups) {
		fileGroups << group->getTitle() << " " << group->getSpeciality() << " ";
		if (group->getHead() != nullptr) {
			fileGroups << group->getHead()->getFio() << "\n";
		}
		else {
			fileGroups << "None\n";
		}
		for (Student* student : group->getStudents()) {
			fileStudents << student->getId() << " " << student->getFio() <<  " " << student->getGroup()->getTitle() << " ";
			for (int mark : student->getMarks()) {
				fileStudents << mark << " ";
			}
			fileStudents << "\n";
		}
	}

	fileGroups.close();
	fileStudents.close();
}

void Deanery::displayData() {
	std::cout << std::endl << "Groups: " << std::endl;
	for (Group* group : groups) {
		std::cout << group->getTitle() << " " << group->getSpeciality() << " ";
		if (group->getHead() != nullptr) {
			std::cout << group->getHead()->getFio() << "\n";
		}
		else {
			std::cout << "None\n";
		}
	}
	std::cout << std::endl;
	std::cout << "Students: " << std::endl;
	for (Group* group : groups) {
		for (Student* student : group->getStudents()) {
			std::cout << student->getId() << " " << student->getFio() << " " << student->getGroup()->getTitle() << " ";
			for (int mark : student->getMarks()) {
				std::cout << mark << " ";
			}
			std::cout << "\n";
		}
	}
}

const std::vector<Group*>& Deanery::getGroups() const {
	return groups;
}

void Deanery::setGroups(const std::vector<Group*>& groups) {
	this->groups = groups;
}