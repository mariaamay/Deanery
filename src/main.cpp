#include <iostream>
#include <string>
#include <vector>
#include "Student.h"
#include "Group.h"
#include "Deanery.h"

int main() {

	std::cout << "Test 1: check Student Class: SetID, SetFIO, GetID, GetFIO" << std::endl;
	Student student;
	student.setId(1); //set ID
	student.setFio("Mayorova Maria Vadimovna"); //set FIO
	if (student.getId() != 1) { //check ID
		std::cout << "SetID/GetID failed" << std::endl;
	}
	else if (student.getFio() != "Mayorova Maria Vadimovna") { //check FIO
		std::cout << "SetFIO/GetFIO failed" << std::endl;
	}
	else {
		std::cout << "Successfully: " << student.getId() << " " << student.getFio() << std::endl;
	}
	std::cout << std::endl;

	std::cout << "Test 2: check Student Class: setMarks, getMarks, addMark, calculateAverageMark" << std::endl;
	std::vector<int> marks = { 9, 10, 8, 7, 7 }; //create vector
	student.setMarks(marks); // set Marks
	student.addMark(10); // add Mark
	if (student.getMarks().size() != marks.size() + 1) { //check marks
		std::cout << "SetMarks/GetMarks/AddMark failed" << std::endl;
	}
	else {
		std::cout << "Successfully: ";
		for (int mark : student.getMarks()) {
			std::cout << mark << " ";
		}
		std::cout << std::endl;
	}	
	std::cout << "The average mark: " << student.calculateAverageMark() << std::endl;
	std::cout << std::endl;
	


	std::cout << "Test 3: check Group Class: group constructor, GetTitle, GetSpeciality, enrollInGroup, GetGroup, SetHead, GetHead" << std::endl;
	Group group("23CST5", "CST"); // create the group
	student.enrollInGroup(&group); // enroll student in the group
	group.setHead(&student); // set student as a head of the group
	if (group.getTitle() != "23CST5" || group.getSpeciality() != "CST") { //check Title
		std::cout << "group constructor/GetTitle/GetSpeciality failed" << std::endl;
	}
	else if (student.getGroup() != &group) { 
		std::cout << "enrollInGroup/GetGroup failed" << std::endl;
	}
	else if (group.getHead() != &student) {
		std::cout << "SetHead/GetHead failed" << std::endl;
	}
	else {
		std::cout << "Successfully: " << group.getTitle() << " " << group.getSpeciality() << " " << group.getHead()->getFio() << std::endl;
		std::cout << student.getId() << " " << student.getFio() << " " << student.getGroup()->getTitle() << std::endl;
	}
	std::cout << std::endl;
	

	std::cout << "Test 4: check Group Class: expellStudent, electHead, getStudent, setStudents, getStudents, calculateAverageMarkGroup" << std::endl;
	Student student2(2, "Parfenov Daniil Alexandrovich"); // new students
	Student student3(3, "Pestov Lev Evgenievich");
	student2.setMarks({ 10, 10, 10, 10, 10 }); //set marks
	student3.setMarks({ 9, 10, 10, 10, 10 });
	std::vector<Student*> students = { &student2, &student3 }; //create vector of students
	group.setStudents(students); //set students
	group.expelStudent(&student); //expel the first student - only new students left
	group.electHead();
	if (group.getStudent(2) != &student2) { //check getStudent by ID
		std::cout << "GetStudent by ID failed" << std::endl;
	}
	if (group.getStudent("Pestov Lev Evgenievich") != &student3) { //check getStudent by FIO
		std::cout << "GetStudent by FIO failed" << std::endl;
	}
	if (!(group.getStudents().empty())) { // check getStudents
		for (Student* student : group.getStudents()) {
			std::cout << student->getId() << " " << student->getFio() << std::endl;
		}
	}
	else {
		std::cout << "setStudents/getStudents failed" << std::endl;
	}
	std::cout << "The head of the group: " << group.getHead()->getFio() << std::endl;
	std::cout << "The average mark of the group: " << group.calculateAverageMarkGroup() << std::endl;
	std::cout << std::endl;

	std::cout << "Test 5: check Deanery Class" << std::endl;
	Deanery deanery;
	deanery.createGroupsFromFile("C:\\Users\\PC\\source\\repos\\Deanery\\bd\\groups.txt");
	deanery.createStudentsFromFile("C:\\Users\\PC\\source\\repos\\Deanery\\bd\\students.txt");
	deanery.expelStudent(68); // this student will be expelled because his average mark is less than 4
	deanery.expelStudent(44); // this student will not be expelled because her average mark is higher than 4
	deanery.addRandomMarksToStudents(); // add random marks
	deanery.getGroups()[2]->electHead(); // elect new head of the 23CST6
	deanery.getStatistics(); // get statictics of all groups
	deanery.getStatistics("23CST5"); // get statictics of 23CST5
	deanery.transferStudent(40, "23CST6"); //transfer student with ID 40 from 23CST5 to 23CST6
	deanery.saveData(); // save data
	deanery.displayData(); //display data
	return 0;
}
