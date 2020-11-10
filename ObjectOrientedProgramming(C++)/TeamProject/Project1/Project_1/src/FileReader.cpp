#include "FileReader.h"

void FileReader::ReadFileToStrVector(string file_name, vector<string> &temp_str_vector)
{
	temp_str_vector.clear(); // clear previous data before writing

	ifstream readfile(file_name, ios::in); // open file stream as read-only mode
	
	if (readfile.is_open())
	{
		string line;

		while (getline(readfile, line))
			temp_str_vector.push_back(line); // appends line content to temp_str_vector
		
		readfile.close();
	}
};