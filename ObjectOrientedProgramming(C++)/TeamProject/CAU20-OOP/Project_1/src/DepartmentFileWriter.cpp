#include "DepartmentFileWriter.h"

DepartmentFileWriter::DepartmentFileWriter()
{
}

void DepartmentFileWriter::ComposeStrVectorFromObj(vector<string> &temp_str_vector, DepartmentManager dept_manager)
{
	temp_str_vector.clear(); // clears previous data

	for (int i = 0; i < dept_manager.get_department_count(); i++)
	{
		// add "code name" formatted string to temporary string vector
		temp_str_vector.push_back(
			dept_manager.get_department_list()[i].get_code() + ' ' +
			dept_manager.get_department_list()[i].get_name());
	}
}