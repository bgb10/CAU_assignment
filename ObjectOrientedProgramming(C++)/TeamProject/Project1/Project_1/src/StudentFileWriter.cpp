#include "StudentFileWriter.h"

StudentFileWriter::StudentFileWriter()
{
}

void StudentFileWriter::ComposeStrVectorFromObj(vector<string> &temp_str_vector, StudentManager stud_manager)
{
	temp_str_vector.clear(); // clears previous data

	for (int i = 0; i < stud_manager.get_student_count(); i++)
	{
		// add "name/id/email/tel" formatted string to temporary string vector
		temp_str_vector.push_back(
			stud_manager.get_student_list()[i].get_name() + '/' +
			stud_manager.get_student_list()[i].get_id() + '/' +
			stud_manager.get_student_list()[i].get_email() + '/' +
			stud_manager.get_student_list()[i].get_tel());
	}
}