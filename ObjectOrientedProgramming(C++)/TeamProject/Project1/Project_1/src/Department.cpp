#include "Department.h"

Department::Department(string code, string name)
{
    set_code(code);
    set_name(name);
}

Department::Department()
{
}

string Department::set_code(string input)
{
    bool condition = false;
	for (auto i : input)
	{
		if (i < '0' || i > '9')
			condition = true;
	}
	if (condition || input.length() != 3)
	{
		return "Error : Department code must be 3 digits.";
	}
	if (input == " ")
	{
		return "Error : Department code must be alphabetic.";
	}
    
    this->code = input;

    return "";
}

string Department::set_name(string input)
{    
    this->name = input;

    return "";
}

string Department::get_code()
{
    return this->code;
}
string Department::get_name()
{
    return this->name;
}