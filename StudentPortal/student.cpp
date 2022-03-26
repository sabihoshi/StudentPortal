#include "student.h"

#include "console.h"

int Student::GetYearLevel()
{
	return YearLevel;
}

int Student::GetId()
{
	return StudentId;
}

std::string Student::GetName()
{
	return Name.First + " " + Name.Last;
}

std::string Student::GetYear()
{
	return "Year " + std::to_string(YearLevel);
}

std::string Student::GetDegree()
{
	return Degree + " " + GetYear();
}

std::string Student::GetBirthday()
{
	std::string month;
	switch (Birthday.Month)
	{
		case 1: month = "Jan";
			break;
		case 2: month = "Feb";
			break;
		case 3: month = "Mar";
			break;
		case 4: month = "Apr";
			break;
		case 5: month = "May";
			break;
		case 6: month = "Jun";
			break;
		case 7: month = "Jul";
			break;
		case 8: month = "Aug";
			break;
		case 9: month = "Sep";
			break;
		case 10: month = "Oct";
			break;
		case 11: month = "Nov";
			break;
		case 12: month = "Dec";
			break;
		default: break;
	}

	return month + " " + std::to_string(Birthday.Day) + ", " + std::to_string(Birthday.Year);
}

std::string Student::GetAddress()
{
	return Address;
}

std::string Student::GetGender()
{
	return Gender;
}

Student Student::CreateStudent()
{
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

	return Student(
		first, last,
		id, level,
		year, month, day,
		address, gender, degree);
}

bool Student::HasSameName(std::string first, std::string last)
{
	return _strcmpi(Name.First.c_str(), first.c_str()) == 0
		&& _strcmpi(Name.Last.c_str(), last.c_str()) == 0;
}

bool Student::HasSameBirthday(int year, int month, int day)
{
	return Birthday.Year == year
		&& Birthday.Month == month
		&& Birthday.Day == day;
}

bool Student::HasSameAddress(std::string address)
{
	return _strcmpi(Address.c_str(), address.c_str()) == 0;
}

bool Student::HasSameGender(std::string gender)
{
	return _strcmpi(Gender.c_str(), gender.c_str()) == 0;
}

bool Student::HasSameDegree(std::string degree)
{
	return _strcmpi(Degree.c_str(), degree.c_str()) == 0;
}

void Student::Display()
{
	WriteLine(
		Right(std::to_string(GetId()), 10) +
		Right(GetName(), 25) +
		Right(GetDegree(), 15) +
		Right(GetBirthday(), 15) +
		Right(GetAddress(), 25) +
		Right(GetGender(), 10));
}
