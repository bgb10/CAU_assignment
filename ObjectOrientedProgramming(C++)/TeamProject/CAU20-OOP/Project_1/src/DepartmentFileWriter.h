#ifndef __DEPARTMENTFILEWRITER_H__
#define __DEPARTMENTFILEWRITER_H__

#include "FileWriter.h"
#include "DepartmentManager.h"

class DepartmentFileWriter : public FileWriter
{
public:
	DepartmentFileWriter();

public:
	void ComposeStrVectorFromObj(vector<string> &temp_str_vector, DepartmentManager dept_manager);
};

#endif