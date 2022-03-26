#include "studentlist.h"

#include <iostream>
#include <fstream>
#include <vector>

#include "console.h"
#include "student.h"

StudentList::StudentList(std::string fileName): _fileName(std::move(fileName))
{
	Load();
}

void StudentList::AddStudent()
{
	system("cls");
	PrintBorders({20, 3}, "ADD STUDENT", 80, 20);

	auto first = Prompt<std::string>("Enter your first name");
	auto last = Prompt<std::string>("Enter your last name");
	auto id = Prompt<int>("Enter your student ID");
	auto level = Prompt<int>("Enter your year level");
	auto year = Prompt<int>("Enter the year you were born");
	auto month = Prompt<int>("Enter the month your were born (1-12)");
	auto day = Prompt<int>("Enter the day you were born");
	auto address = Prompt<std::string>("Enter your Address");
	auto gender = Prompt<std::string>("Enter your Gender");
	auto degree = Prompt<std::string>("Enter your Degree");
	auto student = Student(
		first, last,
		id, level,
		year, month, day,
		address, gender, degree);

	Add(student);
	Save();
}

void StudentList::SearchStudent()
{
	system("cls");
	PrintBorders({ 20, 3 }, "SEARCH STUDENT", 80, 20);

	XY(53, 7);
	Color yellow{ 232, 182, 30 };
	WriteLine(ChangeColor("1", yellow) + ". Name");
	WriteLine(ChangeColor("2", yellow) + ". Student ID");
	WriteLine(ChangeColor("3", yellow) + ". Year Level");
	WriteLine(ChangeColor("4", yellow) + ". Birthday");
	WriteLine(ChangeColor("5", yellow) + ". Address");
	WriteLine(ChangeColor("6", yellow) + ". Gender");
	WriteLine(ChangeColor("7", yellow) + ". Degree");

	std::vector<Student> filtered;
Prompt:
	const int criteria = Prompt<int>("Search with what field", {25, 17});
	switch (criteria)
	{
		case 1:
		{
			std::string first = Prompt<std::string>("Enter first name");
			std::string last = Prompt<std::string>("Enter last name");
			filtered = Where([&](Student& s) -> bool
			{
				return s.HasSameName(first, last);
			});
			break;
		}
		case 2:
		{
			int id = Prompt<int>("Enter student ID");
			filtered = Where([&](Student& s) -> bool
			{
				return s.GetId() == id;
			});
			break;
		}
		case 3:
		{
			int level = Prompt<int>("Enter year level");
			filtered = Where([&](Student& s) -> bool
			{
				return s.GetYearLevel() == level;
			});
			break;
		}
		case 4:
		{
			int year = Prompt<int>("Enter year");
			int month = Prompt<int>("Enter month");
			int day = Prompt<int>("Enter day");
			filtered = Where([&](Student& s) -> bool
			{
				return s.HasSameBirthday(year, month, day);
			});
			break;
		}
		case 5:
		{
			std::string address = Prompt<std::string>("Enter address");
			filtered = Where([&](Student& s) -> bool
			{
				return s.HasSameAddress(address);
			});
			break;
		}
		case 6:
		{
			std::string gender = Prompt<std::string>("Enter gender");
			filtered = Where([&](Student& s) -> bool
			{
				return s.HasSameGender(gender);
			});
			break;
		}
		case 7:
		{
			std::string degree = Prompt<std::string>("Enter degree");
			filtered = Where([&](Student& s) -> bool
			{
				return s.HasSameDegree(degree);
			});
			break;
		}
		default: goto Prompt;
	}

	DisplayStudents(filtered);
}

void StudentList::DisplayStudents()
{
	DisplayStudents(ToVector());
}

void StudentList::DisplayStudent()
{
	system("cls");
	PrintBorders({ 10, 3 }, "DISPLAY STUDENT", 120, 20);

	const auto id = Prompt<int>("Enter the ID of the student you want to display");
	auto student = Find([&](Student& s) -> bool
	{
		return s.GetId() == id;
	});

	if (student == nullptr)
	{
		WriteLine("Student was not found");
	}
	else
	{
		student->Display();
	}
}

void StudentList::DeleteStudent()
{
	system("cls");
	PrintBorders({ 10, 3 }, "DELETE STUDENT", 120, 20);

	const int id = Prompt<int>("Enter student ID you want to delete");
	const auto removed = Delete([&](Student& s) -> bool
	{
		return s.GetId() == id;
	});

	if (removed == nullptr)
	{
		WriteLine("Student was not found");
	}
	else
	{
		removed->Display();
		WriteLine("Deleted student");
	}
}

void StudentList::AddStudent(Student student)
{
	_students.Add(student);
}

void StudentList::DisplayStudents(std::vector<Student> students)
{
	system("cls");
	PrintBorders({5, 3}, "STUDENT LIST", 110, 20);
	WriteLine(
		Right("ID", 10) +

		Right("Name", 25) +
		Right("Degree", 15) +
		Right("Birthday", 15) +
		Right("Address", 25) +
		Right("Gender", 10));
	for (auto& student : students)
	{
		student.Display();
	}
}

void StudentList::Load()
{
	std::ifstream file(_fileName);
	try
	{
		nlohmann::json j;
		file >> j;
		const auto list = j.get<std::vector<Student>>();
		for (const auto& item : list)
			Add(item);
	}
	catch (nlohmann::detail::parse_error& p)
	{
		std::cerr << "Failed to open file at byte " << p.byte << std::endl;
		std::cerr << "No students were loaded." << std::endl;
	}
}

void StudentList::Save()
{
	std::ofstream file(_fileName);
	auto list = ToVector();
	const nlohmann::json j = list;
	file << std::setw(4) << j;
}
