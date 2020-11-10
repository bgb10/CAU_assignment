#ifndef __STUDENTMANAGER_H__
#define __STUDENTMANAGER_H__

#include <vector>
#include "Student.h"
#include "DepartmentManager.h"

class StudentManager
{
	// Variables
private:
	vector<Student> student_list;
	int sort_option;

	// member functions
public:
	void InsertStudent(Student student);
	vector<Student> SearchStudents(int search_option, string query);

	vector<Student> FindStudentsByName(string name);
	vector<Student> FindStudentsByID(string id);
	vector<Student> FindStudentsByAdmissionYear(string admission_year);
	vector<Student> FindStudentsByDepartmentName(string department_name);

	// setter
public:
	void set_sort_option(int sort_option);
	void set_student_list(vector<Student> student_list);
	void set_department_name(DepartmentManager& dept_manager);

private:
	void SortByName();
	void SortByID();
	void SortByDepartmentName();

	// getter
public:
	vector<Student> get_student_list();
	int get_sort_option();
	int get_student_count();
};

#endif