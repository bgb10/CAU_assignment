#ifndef __STUDENTFILEWRITER_H__
#define __STUDENTFILEWRITER_H__

#include "FileWriter.h"
#include "StudentManager.h"

class StudentFileWriter : public FileWriter
{
public:
	StudentFileWriter();

public:
	void ComposeStrVectorFromObj(vector<string> &temp_str_vector, StudentManager stud_manager);
};

#endif