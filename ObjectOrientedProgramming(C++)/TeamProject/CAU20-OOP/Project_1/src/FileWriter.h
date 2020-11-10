#ifndef __FILEWRITER_H__
#define __FILEWRITER_H__

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class FileWriter
{
public:
	void WriteFileFromStrVector(string file_name, vector<string> temp_str_vector);
};

#endif