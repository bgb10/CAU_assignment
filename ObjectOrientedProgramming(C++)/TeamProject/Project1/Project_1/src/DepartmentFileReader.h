#ifndef __DEPARTMENTFILEREADER_H__
#define __DEPARTMENTFILEREADER_H__

#include "FileReader.h"
#include "DepartmentManager.h"

class DepartmentFileReader : public FileReader
{
public:
	void ParseStrVectorToObj(vector<string> temp_str_vector, DepartmentManager &dept_manager);
};

#endif