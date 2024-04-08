#include "Student.h"

Student::Student(int id, const std::string& fio) : id(id), fio(fio), group(nullptr) {}

void Student::enrollInGroup(Group* group) {
	if (group == nullptr) {
		std::cerr << "Error: Cannot enroll the student in a null group" << std::endl;
		return;
	}
	this->group = group;
	group->addStudent(this);
}

void Student::addMark(int mark) {
	if (mark < 0 || mark > 10) {
		std::cerr << "Error: Invalild mark value" << std::endl;
		return;
	}
	marks.push_back(mark);
}

double Student::calculateAverageMark() {
	if (marks.empty()) {
		return 0.0;
	}
	else {
		int sum = 0;
		for (int mark: marks) {
			sum += mark;
		}
		return static_cast<double> (sum) / marks.size();
	}
}

int Student::getId() const {
	return id;
}

const std::string& Student::getFio() const {
	return fio;
}

Group* Student::getGroup() const {
	return group;
}

const std::vector<int>& Student::getMarks() const {
	return marks;
}

void Student::setId(int id) {
	this->id = id;
}

void Student::setFio(const std::string& fio) {
	this->fio = fio;
}

void Student::setGroup(Group* group) {
	this->group = group;
}

void Student::setMarks(const std::vector<int>& marks) {
	this->marks = marks;
}
