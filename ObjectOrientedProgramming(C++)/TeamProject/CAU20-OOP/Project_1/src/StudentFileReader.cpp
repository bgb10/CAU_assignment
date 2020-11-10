#include <regex>
#include "StudentFileReader.h"

void StudentFileReader::ParseStrVectorToObj(vector<string> temp_str_vector, StudentManager &stud_manager)
{
    // regular expression to check whether the input is correct or not
    // Explanation of the regular expression below
    // Capture group 1 ([\w|\s]+)    : any character or whitespace
    // Capture group 2 (\d{10})      : exactly 10 digits
    // Capture group 3 (\w+@\w+\.\w+): email format (a@a.a where a is any string)
    // Capture group 4 (\d+)         : digits of any length
    // All capture groups are divided in '/', as in the text file
    regex rgx("([\\w|\\s]+)\\/(\\d+)\\/(\\w+@\\w+\\.\\w+)\\/(\\d+)");
    smatch matches;

    for (int i = 0; i < temp_str_vector.size(); i++)
    {
        string s = temp_str_vector[i];

        // cout << "StudentFileReader::ParseStrVectorToObj : Read string '" + s + "'" << endl;

        if (regex_search(s, matches, rgx))
        {
            // cout << "StudentFileReader::ParseStrVectorToObj : Regex match count is " << matches.size() << endl;
            
            // insert student data only if the regex match returns 1 match string + 4 results
            // results should be name, id, email, tel in order
            // group match results are from index 1
            if (matches.size() == 5)
            {
                stud_manager.InsertStudent(Student(
                    matches[1].str(), // name
                    matches[2].str(), // id
                    matches[3].str(), // email
                    matches[4].str()  // tel
                    ));

                // cout << "Added student: " + matches[1].str() + " / " + matches[2].str() + " / " + matches[3].str() + " / " + matches[4].str() << endl;
            }
        }
        else
        {
            // TODO: add wrong input error
        }
    }
}