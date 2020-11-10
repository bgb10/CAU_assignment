#include "DepartmentManager.h"

//public member functions
void DepartmentManager::InsertDepartment(Department department)
{
    department_list.push_back(department);
}

string DepartmentManager::FindName(string code)
{
    for (int i = 0; i < get_department_count(); i++)
    {
        if (department_list[i].get_code() == code)
        {
            return department_list[i].get_name();
        }
    }

    //If error returns, UI shows error message.
    return "Error : Department code doesn't exist.";
}
string DepartmentManager::FindCode(string name)
{
    for (int i = 0; i < get_department_count(); i++)
    {
        if (department_list[i].get_name() == name)
        {
            return department_list[i].get_code();
        }
    }

    //If error returns, UI shows error message.
    return "Error : Department name doesn't exist";
}

bool DepartmentManager::IsCodeExists(string code)
{
    for (int i = 0; i < get_department_count(); i++)
    {
        if (department_list[i].get_code() == code)
        {
            return true;
        }
    }

    return false;
}

bool DepartmentManager::IsNameExists(string name)
{
    for (int i = 0; i < get_department_count(); i++)
    {
        if (department_list[i].get_name() == name)
        {
            return true;
        }
    }

    return false;
}

// setters
void DepartmentManager::set_department_list(vector<Department> department_list)
{
    this->department_list = department_list;
}

// getters
int DepartmentManager::get_department_count()
{
    return department_list.size();
}

vector<Department> DepartmentManager::get_department_list()
{
    return department_list;
}
