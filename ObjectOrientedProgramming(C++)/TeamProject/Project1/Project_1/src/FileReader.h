#ifndef __FILEREADER_H__
#define __FILEREADER_H__

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class FileReader
{
public:
    void ReadFileToStrVector(string file_name, vector<string> &temp_str_vector);
};

#endif