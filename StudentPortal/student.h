#pragma once

#include <ctime>
#include <iostream>
#include <string>

#include "json.hpp"
#include "linkedlist.h"

struct Birthday
{
	int Year;
	int Month;
	int Day;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Birthday, Year, Month, Day);
};

struct Name
{
	std::string First;
	std::string Last;

	bool operator==(const Name& other) const
	{
		return First == other.First && Last == other.Last;
	}

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Name, First, Last);
};

struct DateRange
{
	std::time_t Start;
	std::time_t End;
};

struct Course
{
	std::string Code;
	std::string Title;
	std::string Section;
	int Units;
	std::string Days;
	DateRange Time;
	std::string Room;
};

struct Socials
{
	std::string Facebook;
	std::string Discord;
};

class Student
{
	

public:
	Student(
		std::string first, std::string last,
		int id, int level,
		int year, int month, int day,
		std::string address, std::string gender, std::string degree)
		: Name({first, last}), StudentId(id),
		  YearLevel(level), Birthday({year, month, day}),
		  Address(address), Gender(gender), Degree(degree) {}

	Student() = default;

	int GetYearLevel();

	int GetId();

	bool HasSameName(std::string, std::string);

	std::string GetName();

	std::string GetYear();

	std::string GetDegree();

	std::string GetBirthday();

	std::string GetAddress();

	std::string GetGender();

	static Student CreateStudent();

	bool HasSameBirthday(int year, int month, int day);

	bool HasSameAddress(std::string address);

	bool HasSameGender(std::string gender);

	bool HasSameDegree(std::string degree);

	void Display();

private:
	Name Name;
	int StudentId;
	int YearLevel;
	Birthday Birthday;
	std::string Address;
	std::string Gender;
	std::string Degree;
	LinkedList<Course> _courses = LinkedList<Course>();
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Student, Name, StudentId, YearLevel, Birthday, Address, Gender, Degree);
};