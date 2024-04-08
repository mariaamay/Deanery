#include "Group.h"

Group::Group(const std::string& title, const std::string& speciality) : title(title), speciality(speciality), head(nullptr) {}

void Group::addStudent(const Student* student) {
	students.push_back(const_cast<Student*> (student));
}

void Group::electHead() {
	if (!students.empty()) {
		double highestAverageMark = -10.0;
		Student* newHead = nullptr;

		for (Student* student : students) {
			if (student->calculateAverageMark() > highestAverageMark) {
				highestAverageMark = student->calculateAverageMark();
				newHead = student;
			}
		}
		setHead(newHead);
	}
}

Student* Group::getStudent(int id) const {
	for (Student* student: students) {
		if (student->getId() == id) {
			return student;
		}
    }
	return nullptr;
}

Student* Group::getStudent(const std::string& fio) const {
	for (Student* student : students) {
		if (student->getFio() == fio) {
			return student;
		}
	}
	return nullptr;
}

double Group::calculateAverageMarkGroup() {
	if (students.empty()) {
		return 0.0;
	}
	double sum = 0.0;
	for (Student* student : students) {
		sum += student->calculateAverageMark();
	}
	return sum / students.size();
}

void Group::expelStudent(const Student* student) {
	for (auto it = students.begin(); it != students.end(); it++) {
		if (*it == student) {
			students.erase(it);
			break;
		}
	}
}

const std::string& Group::getTitle() const {
	return title;
}

const std::string& Group::getSpeciality() const {
	return speciality;
}

const std::vector<Student*>& Group::getStudents() const {
	return students;
}

Student* Group::getHead() const {
	return head;
}

void Group::setTitle(const std::string& title) {
	this->title = title;
}

void Group::setSpeciality(const std::string& speciality) {
	this->speciality = speciality;
}

void Group::setStudents(const std::vector<Student*>& students) {
	this->students = students;
}

void Group::setHead(Student* head) {
	this->head = head;
}