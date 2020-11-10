#include "inf_int.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <regex>

using namespace std;

int main()
{
	string str_line;
	string str_a;
	string str_b;
	char char_op;
	
	char* char_a;
	char* char_b;

	int pos;
	inf_int inf_c;
	
	while (1) {
		cout << "Input : ";

		getline(cin, str_line);
		if (str_line == "0") break;

		pos = str_line.find(' ');
		str_a = str_line.substr(0, pos);
		char_op = str_line[pos + 1];
		str_b = str_line.substr(pos + 3);

		char_a = new char[str_a.length() + 1];
		char_b = new char[str_b.length() + 1];

		strcpy(char_a, str_a.c_str());
		strcpy(char_b, str_b.c_str());

		inf_int inf_a(char_a);
		inf_int inf_b(char_b);

		switch (char_op) {
			case '+':
				inf_c = inf_a + inf_b;
				break;
			case '-':
				inf_c = inf_a - inf_b;
				break;
			case '*':
				inf_c = inf_a * inf_b;
				break;
			default:
				cout << "Wrong operator!!" << endl;
				break;
		}

		cout << "Output: " << inf_c << endl;

		delete[] char_a;
		delete[] char_b;
	}

	return 0;
}
