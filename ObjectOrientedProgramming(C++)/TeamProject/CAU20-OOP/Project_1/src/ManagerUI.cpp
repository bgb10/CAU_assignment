#include <iostream>
#include <cstdio>
#include <string>
#include <vector>

#include "ManagerUI.h"
#include "Student.h"
#include "StudentManager.h"
#include "Department.h"
#include "DepartmentManager.h"

using namespace std;

void PrintSearchResult(vector<Student> student_list)
{
	if (student_list.empty())
		cout << "No information found." << endl;
	else
	{
		// Print column title and divider
		printf("%-15s | %s | %-30s | %-15s | %-10s\n", "Name", "Student ID", "Department", "Email", "Tel");
		printf("----------------+------------+--------------------------------+-----------------+------------\n");

		// Print student data in list
		for (unsigned int i = 0; i < student_list.size(); i++)
		{
			printf("%-15s | %s | %-30s | %-15s | %-10s\n",
				   student_list[i].get_name().c_str(),
				   student_list[i].get_id().c_str(),
				   student_list[i].get_department_name().c_str(),
				   student_list[i].get_email().c_str(),
				   student_list[i].get_tel().c_str());
		}
	}
}

ManagerUI::ManagerUI(StudentManager *stud_manager, DepartmentManager *dept_manager)
{
	this->stud_manager = stud_manager;
	this->dept_manager = dept_manager;
}

void ManagerUI::Initialize()
{
	string input;

	stud_manager->set_sort_option(1);

	cout << "Student Information Management System" << endl;

	while (1)
	{
		cout << endl;
		cout << "[ Main menu ]" << endl << endl;
		cout << "1. Insertion" << endl;
		cout << "2. Search" << endl;
		cout << "3. Sorting Option" << endl;
		cout << "4. Department Insertion" << endl;
		cout << "5. Exit" << endl;
		cout << "> ";

		cin >> input;

		cout << endl;

		if (input == "1")
		{
			StudentInsertion();
		}
		else if (input == "2")
		{
			Search();
		}
		else if (input == "3")
		{
			SetSortingOption();
		}
		else if (input == "4")
		{
			DepartmentInsertion();
		}
		else if (input == "5")
		{
			cout << "Exiting the program." << endl;
			break;
		}
		else
		{
			cout << endl << "Error : Input '" << input << "' is not a valid option." << endl;
		}
	}
}

void ManagerUI::StudentInsertion()
{
	Student student = Student();
	string input;
	string stud_message_str;
	vector<Student> temp_stud_vector;
	bool condition;
	
	cout << "[ Insertion ]" << endl << endl;

	/* Name Insertion */
	cout << "Name ? ";
	getline(cin, input); // Prevents skipping the input
	getline(cin, input);
	stud_message_str = student.set_name(input);
	if (stud_message_str != "")
	{
		cout << endl << stud_message_str << endl;
		return;
	}

	/* Student ID Insertion */
	cout << "Student ID ? ";
	cin >> input;
	temp_stud_vector = stud_manager->FindStudentsByID(input);
	if (!temp_stud_vector.empty())
	{
		cout << endl << "Error : Already inserted. A student with the same student ID exists." << endl;
		return;
	}
	stud_message_str = student.set_id(input);
	if (stud_message_str != "")
	{
		cout << endl << stud_message_str << endl;
		return;
	}
	if (!dept_manager->IsCodeExists(input.substr(4, 3)))
	{
		cout << endl << "Error : Department code '" << input.substr(4, 3) << "' doesn't exist." << endl;
		return;
	}
	/* Department Name Insertion */
	student.set_department_name(dept_manager->FindName(student.get_department_code()));

	/* Email Insertion */
	cout << "Email address ? ";
	cin >> input;
	stud_message_str = student.set_email(input);
	if (stud_message_str != "")
	{
		cout << endl << stud_message_str << endl;
		return;
	}

	/* Tel Insertion */
	cout << "Tel ? ";
	cin >> input;
	stud_message_str = student.set_tel(input);
	if (stud_message_str != "")
	{
		cout << endl << stud_message_str << endl;
		return;
	}
	stud_manager->InsertStudent(student);

	cout << endl << "Successfully inserted a student with following information." << endl << endl;
	PrintSearchResult({student});

	stud_manager->set_sort_option(1);
}

void ManagerUI::Search()
{
	vector<Student> temp_stud_vector;
	string input;
	bool condition;
	cout << "[ Search ]" << endl << endl;
	cout << "1. Search by name" << endl;
	cout << "2. Search by student id (10 numbers)" << endl;
	cout << "3. Search by admission year (4 numbers)" << endl;
	cout << "4. Search by department name" << endl;
	cout << "5. List all" << endl;
	cout << "> ";

	cin >> input;

	cout << endl;

	if (input == "1")
	{
		cout << "Name ? ";
		getline(cin, input); // Prevents skipping the input
		getline(cin, input);
		if (input.length() > 15)
		{
			cout << endl << "Error : Name must be shorter or equal to 15 characters." << endl;
			return;
		}
		if (input == " ")
		{
			cout << endl << "Error : Name must be alphabetic." << endl;
			return;
		}
		cout << endl;
		condition = false;
		for (auto &i : input)
		{
			if (!((i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z') || i == ' '))
				condition = true;
		}
		if (condition)
		{
			cout << endl << "Error : Name must be alphabetic." << endl;
		}

		PrintSearchResult(stud_manager->SearchStudents(1, input));
	}
	else if (input == "2")
	{
		cout << "Student ID ? ";
		cin >> input;
		if (input == " ")
		{
			cout << endl << "Error : Student ID must not be spaces." << endl;
			return;
		}
		condition = false;
		for (auto &i : input)
		{
			if (i < '0' || i > '9')
				condition = true;
		}
		if (condition || input.length() != 10)
		{
			cout << endl << "Error : Student ID must be 10 digits." << endl;
			return;
		}
		cout << endl;
		PrintSearchResult(stud_manager->SearchStudents(2, input));
	}
	else if (input == "3")
	{
		cout << "Admission year ? ";
		cin >> input;
		condition = false;
		for (auto &i : input)
		{
			if (i < '0' || i > '9')
				condition = true;
		}
		if (condition || input.length() != 4)
		{
			cout << endl << "Error : Admission year must be 4 digits." << endl;
			return;
		}
		if (input == " ")
		{
			cout << endl << "Error : Admission year must be a number." << endl;
			return;
		}
		cout << endl;
		PrintSearchResult(stud_manager->SearchStudents(3, input));
	}
	else if (input == "4")
	{
		cout << "Department name ? ";
		getline(cin, input); // Prevents skipping the input
		getline(cin, input);
		condition = false;
		for (auto &i : input)
		{
			if (!((i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z') || (i == ' ') || (i == '&')))
				condition = true;
		}
		if (condition)
		{
			cout << endl << "Error : Department name must be alphabetic." << endl;
			return;
		}
		cout << endl;
		PrintSearchResult(stud_manager->SearchStudents(4, input));
	}
	else if (input == "5")
	{
		PrintSearchResult(stud_manager->SearchStudents(5, ""));
	}
	else
	{
		cout << endl << "Error : Input '" << input << "' is not valid." << endl;
	}
}

void ManagerUI::SetSortingOption()
{
	string input;
	cout << "[ Sorting Option ]" << endl << endl;
	cout << "1. Sort by name" << endl;
	cout << "2. Sort by student ID" << endl;
	cout << "3. Sort bt department name" << endl;
	cout << "> ";
	cin >> input;
	if (input == "1")
	{
		stud_manager->set_sort_option(1);
		cout << endl << "Successfully changed sorting option to ascending name order." << endl;
	}
	else if (input == "2")
	{
		stud_manager->set_sort_option(2);
		cout << endl << "Successfully changed sorting option to ascending student ID order." << endl;
	}
	else if (input == "3")
	{
		stud_manager->set_sort_option(3);
		cout << endl << "Successfully changed sorting option to ascending department name order." << endl;
	}
	else
	{
		cout << endl << "Error : Input '" << input << "' is not valid." << endl;
	}
}

void ManagerUI::DepartmentInsertion()
{
	Department department = Department();
	string input;
	string dept_message_string;

	cout << "Department code ? ";
	cin >> input;
	if (dept_manager->IsCodeExists(input))
	{
		cout << endl << "Error : Already inserted. A department with the same department code exists." << endl;
		return;
	}
	dept_message_string = department.set_code(input);
	if (dept_message_string != "")
	{
		cout << endl << dept_message_string << endl;
		return;
	}

	cout << "Department name ? ";
	getline(cin, input); // Prevents skipping the input
	getline(cin, input);
	if (dept_manager->IsNameExists(input))
	{
		cout << endl << "Error : Already inserted. A department with the same department name exists." << endl;
		return;
	}
	dept_message_string = department.set_name(input);
	if (dept_message_string != "")
	{
		cout << endl << dept_message_string << endl;
		return;
	}

	dept_manager->InsertDepartment(department);

	cout << endl << "Successfully inserted a department with following information." << endl << endl;
	
	printf("%-15s | %-30s\n", "Department code", "Department name");
	printf("----------------+--------------------------------\n");
	printf("%-15s | %-30s\n", department.get_code().c_str(), department.get_name().c_str());
}