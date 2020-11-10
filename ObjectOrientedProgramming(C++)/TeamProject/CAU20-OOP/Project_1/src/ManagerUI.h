#ifndef __MANAGERUI_H__
#define __MANAGERUI_H__

#include "StudentManager.h"
#include "DepartmentManager.h"

class ManagerUI
{
private:
    StudentManager* stud_manager;
    DepartmentManager* dept_manager;

public:
    ManagerUI(StudentManager *stud_manager, DepartmentManager *dept_manager);

public:
    void Initialize();
    void StudentInsertion();
    void Search();
    void SetSortingOption();
    void DepartmentInsertion();
};

#endif
