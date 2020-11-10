#include <algorithm>
#include "StudentManager.h"

// public member functions
void StudentManager::InsertStudent(Student student)
{
	student_list.push_back(student);
}

vector<Student> StudentManager::SearchStudents(int search_option, string query)
{
	// switch-case clause here don't need break statements since it has return statement
	switch (search_option)
	{
	case 1:
		return FindStudentsByName(query);
	case 2:
		return FindStudentsByID(query);
	case 3:
		return FindStudentsByAdmissionYear(query);
	case 4:
		return FindStudentsByDepartmentName(query);
	case 5:
		return student_list;
	default:
		// return an empty vector<Student> with wrong search_option
		// TODO: add an exception case or way to prevent errornous inputs
		return vector<Student>();
	}
}

vector<Student> StudentManager::FindStudentsByName(string name)
{
	vector<Student> result_list;
	for (int i = 0; i < get_student_count(); i++)
	{
		if (student_list[i].get_name() == name)
			result_list.push_back(student_list[i]);
	}
	return result_list;
}

vector<Student> StudentManager::FindStudentsByID(string id)
{
	vector<Student> result_list;
	for (int i = 0; i < get_student_count(); i++)
	{
		if (student_list[i].get_id() == id)
		{
			result_list.push_back(student_list[i]);
			break; // no need to iterate more -> id is unique attribute
		}
	}
	return result_list;
}

vector<Student> StudentManager::FindStudentsByAdmissionYear(string admission_year)
{
	vector<Student> result_list;
	for (int i = 0; i < get_student_count(); i++)
	{
		string id = student_list[i].get_id();
		// string.find(str) function returns str's start position
		// if admission_year exists in string id, it must return 0, which is the starting position
		if (id.find(admission_year) == 0)
			result_list.push_back(student_list[i]);
	}
	return result_list;
}

vector<Student> StudentManager::FindStudentsByDepartmentName(string department_name)
{
	vector<Student> result_list;
	for (int i = 0; i < get_student_count(); i++)
	{
		if (student_list[i].get_department_name().find(department_name) != string::npos)
			result_list.push_back(student_list[i]);
	}
	return result_list;
}

// setters
void StudentManager::set_sort_option(int sort_option)
{
	this->sort_option = sort_option;
	switch (sort_option)
	{
	case 1:
		SortByName();
		break;
	case 2:
		SortByID();
		break;
	case 3:
		SortByDepartmentName();
		break;
	default:
		// TODO: add an exception case or way to prevent errornous inputs
		break;
	}
}

void StudentManager::set_student_list(vector<Student> student_list)
{
	this->student_list = student_list;
}

void StudentManager::set_department_name(DepartmentManager& dept_manager)
{
	for (int i = 0; i < get_student_count(); i++)
	{
		Student& student = student_list[i];
		// sets department name with department code in student ID
		student.set_department_name(dept_manager.FindName(student.get_department_code()));
	}
}

// comparing code from https://www.geeksforgeeks.org/sorting-a-vector-in-c/
bool compareName(Student lhs, Student rhs)
{
	// result is in ascending(a-z) order
	return lhs.get_name() < rhs.get_name();
}

void StudentManager::SortByName()
{
	// sorting code is from https://stackoverflow.com/a/26295515/4524257
	sort(student_list.begin(), student_list.end(), compareName);
}

bool compareID(Student lhs, Student rhs)
{
	// result is in ascending(1-9) order
	return lhs.get_id() < rhs.get_id();
}

void StudentManager::SortByID()
{
	sort(student_list.begin(), student_list.end(), compareID);
}

bool compareDepartmentName(Student lhs, Student rhs)
{
	// result is in ascending(a-z) order
	return lhs.get_department_name() < rhs.get_department_name();
}

void StudentManager::SortByDepartmentName()
{
	sort(student_list.begin(), student_list.end(), compareDepartmentName);
}

// getters
vector<Student> StudentManager::get_student_list()
{
	return student_list;
}

int StudentManager::get_sort_option()
{
	return sort_option;
}

int StudentManager::get_student_count()
{
	return student_list.size();
}
