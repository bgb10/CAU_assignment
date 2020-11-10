#ifndef __STUDENTFILEREADER_H__
#define __STUDENTFILEREADER_H__

#include "FileReader.h"
#include "Student.h"
#include "StudentManager.h"

class StudentFileReader : public FileReader
{
public:
    void ParseStrVectorToObj(vector<string> temp_str_vector, StudentManager &stud_manager);
};

#endif