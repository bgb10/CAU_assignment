#ifndef DEPARTMENTMANAGER_H
#define DEPARTMENTMANAGER_H

#include <vector>
#include "Department.h"

class DepartmentManager
{
    // variables
private:
    vector<Department> department_list;

    // member functions
public:
    void InsertDepartment(Department department);
    string FindName(string code);
    string FindCode(string name);
    bool IsCodeExists(string code);
    bool IsNameExists(string name);

    // setters
public:
    void set_department_list(vector<Department> department_list);

    // getters
public:
    int get_department_count();
    vector<Department> get_department_list();
};

#endif