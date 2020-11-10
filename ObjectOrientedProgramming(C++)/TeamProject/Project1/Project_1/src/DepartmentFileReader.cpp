#include <regex>
#include "DepartmentFileReader.h"
#include "Department.h"

void DepartmentFileReader::ParseStrVectorToObj(vector<string> temp_str_vector, DepartmentManager &dept_manager)
{
    // regular expression to check whether the input is correct or not
    // Explanation of the regular expression below
    // Capture group 1 (\d{3})      : exactly 3 digits
    // Capture group 2 ([\w|\s]*\w+): any character or whitespace, but ending with a character
    // Capture groups are divided in ' ', as in the text file
    regex rgx("(\\d{3}) ([\\w|\\s|\\&]*\\w+)");
    smatch matches;

    for (int i = 0; i < temp_str_vector.size(); i++)
    {
        string s = temp_str_vector[i];

        if (regex_search(s, matches, rgx))
        {
            // insert student data only if the regex match returns 1 match string + 2 results
            // results should be department code, department name in order
            // group match results are from index 1
            if (matches.size() == 3)
            {
                dept_manager.InsertDepartment(Department(
                    matches[1].str(), // code
                    matches[2].str()  // name
                    ));

                // cout << "Added department: " + matches[1].str() + " / " + matches[2].str() << endl;
            }
        }
        else
        {
            // TODO: add wrong input error
        }
    }
}