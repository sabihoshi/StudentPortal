#pragma once

#include "linkedlist.h"
#include "student.h"

class StudentList : LinkedList<Student>
{
public:
	explicit StudentList(std::string fileName);

	void AddStudent();

	void AddStudent(Student);

	void SearchStudent();

	void DisplayStudents();

	void DisplayStudent();

	void DeleteStudent();

	void Load();

	void Save();

private:
	std::string _fileName;

	LinkedList<Student> _students;

	void DisplayStudents(std::vector<Student> students);
};
