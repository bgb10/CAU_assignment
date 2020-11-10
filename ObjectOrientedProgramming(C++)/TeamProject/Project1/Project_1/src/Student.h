#ifndef __STUDENT_H__
#define __STUDENT_H__

#include <string>

using namespace std;

class Student
{
private:
	// variables
	string name;
	string id;
	string email;
	string tel;
	string department_name;

public:
	// constructor
	Student();
	Student(string name, string id, string email, string tel);

	// getter
	string get_name();
	string get_id();
	string get_email();
	string get_tel();
	string get_department_name();
	string get_department_code();
	string get_admission_year();

	// setter
	string set_name(string input);
	string set_id(string input);
	string set_email(string input);
	string set_tel(string input);
	string set_department_name(string input);
};

#endif
