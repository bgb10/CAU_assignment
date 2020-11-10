#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <string>

using namespace std;

class Department
{
private:
    string name; // words with whitespaces. e.g., "Computer Science"
    string code; // 3 digit number in string e.g., "034"
public:
    Department(string code, string name);
    Department();
    string get_code();
    string get_name();
    string set_code(string input);
    string set_name(string input);
};

#endif