#include "StudentManager.h"
#include "DepartmentManager.h"
#include "StudentFileReader.h"
#include "StudentFileWriter.h"
#include "DepartmentFileReader.h"
#include "DepartmentFileWriter.h"
#include "ManagerUI.h"

using namespace std;

/**
 * Initializes the program with components.
 */
int main(int argc, char **argv)
{
	// Temporary string vector to hold file input/output values
	vector<string> temp_str_vector;

	// Error handling if any one of the data files are missing
	// Actual program execution arguments starts from index 1 of argv
	if (argc != 3)
	{
		// TODO: add error handling
		return -1;
	}

	// Read and load student data from file
	StudentFileReader stud_file_reader;
	StudentManager stud_manager;

	// Pass str_vector reference to make it editable in the calling function
	stud_file_reader.ReadFileToStrVector(argv[1], temp_str_vector);
	stud_file_reader.ParseStrVectorToObj(temp_str_vector, stud_manager);

	DepartmentFileReader dept_file_reader;
	DepartmentManager dept_manager;

	dept_file_reader.ReadFileToStrVector(argv[2], temp_str_vector);
	dept_file_reader.ParseStrVectorToObj(temp_str_vector, dept_manager);

	// Give dept_manager's info to stud_manager.
	stud_manager.set_department_name(dept_manager);

	// Set ManagerUI data managers
	ManagerUI manager_UI(&stud_manager, &dept_manager);

	// Initialize UI
	manager_UI.Initialize();

	// Save and exit
	StudentFileWriter stud_file_writer;

	stud_file_writer.ComposeStrVectorFromObj(temp_str_vector, stud_manager);
	stud_file_writer.WriteFileFromStrVector(argv[1], temp_str_vector);

	DepartmentFileWriter dept_file_writer;

	dept_file_writer.ComposeStrVectorFromObj(temp_str_vector, dept_manager);
	dept_file_writer.WriteFileFromStrVector(argv[2], temp_str_vector);

	return 0;
}