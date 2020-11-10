#include "Student.h"

// constructor
Student::Student()
{
}

Student::Student(string name, string id, string email, string tel)
{
	set_name(name);
	set_id(id);
	set_email(email);
	set_tel(tel);
}

// getter
string Student::get_name()
{
	return name;
}

string Student::get_id()
{
	return id;
}

string Student::get_email()
{
	return email;
}

string Student::get_tel()
{
	return tel;
}

string Student::get_department_name()
{
	return department_name;
}

string Student::get_department_code()
{
	// student ID is formatted as "YYYYDEPIDN" (addmission year/department code/identifier)
	// substring 3 characters from index 4 to get "DEP" (department code)
	return id.substr(4, 3);
}

string Student::get_admission_year()
{
	// student ID is formatted as "YYYYDEPIDN" (addmission year/department code/identifier)
	// substring 4 characters from index 0 to get "YYYY" (admission year)
	return id.substr(0, 4);
}

// setter
string Student::set_name(string input)
{
	bool condition;

	if (input.length() > 15)
	{	
		return "Error : Name must not be more than 15 characters.";
	}
	if (input == " ")
	{
		return "Error : Name must be alphabetic.";
	}
	condition = false;
	for (auto &i : input)
	{
		if (!((i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z') || i == ' '))
			condition = true;
	}
	if (condition)
	{
		return "Error : Name must be alphabetic.";
	}

	this->name = input;

	return "";
}

string Student::set_id(string input)
{
	bool condition;

	if (input == " ")
	{
		return "Error : Student ID must be numbers.";
	}
	condition = false;
	for (auto &i : input)
	{
		if (i < '0' || i > '9')
			condition = true;
	}
	if (condition || input.length() != 10)
	{
		return "Error : Student ID must be 10 digits.";
	}


	this->id = input;

	return "";
}

string Student::set_email(string input)
{
	bool condition;

	if (input.length() > 15)
	{
		return "Error : Email address must be no more than 15 characters.";
	}
	condition = false;
	for (auto &i : input)
	{
		if (i == '@')
			condition = true;
	}
	if (!condition)
	{
		return  "Error : Email address must be in an email format (a@a.com).";
	}
	
	this->email = input;

	return "";
}

string Student::set_tel(string input)
{
	bool condition;

	condition = false;
	for (auto &i : input)
	{
		if (i < '0' || i > '9')
			condition = true;
	}
	if (condition)
	{
		return "Error : Tel must be numeric.";
	}
	if (input.length() > 12)
	{
		return "Error : Tel must be shorter or equal to 12 digits.";
	}

	this->tel = input;

	return "";
}

string Student::set_department_name(string input)
{
	this->department_name = input;

	return "";
}