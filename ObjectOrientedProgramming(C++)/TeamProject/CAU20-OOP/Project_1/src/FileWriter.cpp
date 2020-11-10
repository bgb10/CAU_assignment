#include "FileWriter.h"

void FileWriter::WriteFileFromStrVector(string file_name, vector<string> temp_str_vector)
{
	ofstream writefile(file_name, ios::trunc); // open file stream as write-only mode

	if (writefile.is_open())
	{
		for (int i = 0; i < temp_str_vector.size(); i++) {
			writefile << temp_str_vector[i] << endl; // writes the temporary string to file
		}

		writefile.close();
	}
}
