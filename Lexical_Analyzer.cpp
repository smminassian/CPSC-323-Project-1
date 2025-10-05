#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cctype>
using namespace std;

string IdentifierFSM(const string &input);
string NumberFSM(const string &input);
string checkKeyword(const string &input);
string checkOperator(const string &input);
string checkSeparator(const string &input);

struct Token
{
	vector<string> token;
	vector<string> lexeme;
};

Token lexer(ifstream &myFile)
{
	Token t;
	char ch;
	cout << "Starting lexical analysis..." << endl;

	string current_lexeme = "";

	if (!myFile)
	{
		cerr << "Error opening file" << endl;
		return t;
	}

	while (myFile.get(ch))
	{
		if (isspace(ch))
		{
			if (isalpha(current_lexeme[0]))
			{
				t.lexeme.push_back(current_lexeme);
				// determine token type here
				t.token.push_back(IdentifierFSM(current_lexeme));

				if (checkKeyword(current_lexeme) != "identifier " + current_lexeme)
				{
					t.token.push_back(checkKeyword(current_lexeme));
				}

				current_lexeme.clear();
				continue;
			}
			else if (isdigit(current_lexeme[0]))
			{
				t.lexeme.push_back(current_lexeme);
				// determine token type here
				t.token.push_back(NumberFSM(current_lexeme));
				// call FSM functions here

				current_lexeme.clear();
				continue;
			}
			else if (checkOperator(current_lexeme) != "invalid")
			{
				t.lexeme.push_back(current_lexeme);
				t.token.push_back(checkOperator(current_lexeme));
				current_lexeme.clear();
				continue;
			}
			else if (checkSeparator(current_lexeme) != "invalid")
			{
				t.lexeme.push_back(current_lexeme);
				t.token.push_back(checkSeparator(current_lexeme));
				current_lexeme.clear();
				continue;
			}
			else
			{
				current_lexeme.clear();
				continue;
			}
		}
		current_lexeme += ch;
	}
	for (int i = 0; i < t.lexeme.size(); i++)
	{
		cout << t.token[i] << " " << t.lexeme[i] << endl;
	}
	return t;
}

const int IdBeginning = 0;
const int IdValid = 1;
const int IdInvalid = 2;

string IdentifierFSM(const string &input)
{
	int state = IdBeginning;

	for (size_t i = 0; i < input.size(); i++)
	{
		char ch = input[i];

		switch (state)
		{
		case IdBeginning:
			if (isalpha(ch) == true)
			{
				state = IdValid;
			}
			else
			{
				state = IdInvalid;
			}
			break;

		case IdValid:
			if (isalnum(ch) == true)
			{
				state = IdValid;
			}
			else
			{
				state = IdInvalid;
			}
			break;

		case IdInvalid:
			break;
		}
		if (state == IdInvalid)
		{
			break;
		}
	}

	if (state == IdValid)
	{
		return "identifier " + input;
	}
	else
	{
		return "invalid";
	}
}

const int NumBeginning = 0;
const int NumInt = 1;
const int NumReal = 2;
const int NumInvalid = 3;

string NumberFSM(const string &input)
{
	int state = NumBeginning;

	for (size_t i = 0; i < input.size(); i++)
	{
		char ch = input[i];

		switch (state)
		{
		case NumBeginning:
			if (isdigit(ch) == true)
			{
				state = NumInt;
			}
			else if (ch == '.')
			{
				state = NumReal;
			}
			else
			{
				state = NumInvalid;
			}
			break;

		case NumInt:
			if (isdigit(ch) == true)
			{
				state = NumInt;
			}
			else if (ch == '.')
			{
				state = NumReal;
			}
			else
			{
				state = NumInvalid;
			}
			break;

		case NumReal:
			if (isdigit(ch) == true)
			{
				state = NumReal;
			}
			else
			{
				state = NumInvalid;
			}

		case NumInvalid:
			break;
		}
		if (state == NumInvalid)
		{
			break;
		}
	}

	if (state == NumInt)
	{
		return "integer " + input;
	}
	else if (state == NumReal)
	{
		return "real " + input;
	}
	else
	{
		return "invalid";
	}
}

string checkKeyword(const string &input)
{
	if (input == "if" || input == "then" || input == "else" || input == "end" || input == "repeat" || input == "until" || input == "read" || input == "write" || input == "begin")
	{
		return "keyword " + input;
	}
	else
	{
		return "identifier " + input;
	}
}

string checkOperator(const string &input)
{
	if (input == "+" || input == "-" || input == "*" || input == "/" || input == "=" || input == "<" || input == ">" || input == "<=" || input == ">=" || input == "!=")
	{
		return "operator " + input;
	}
	else
	{
		return "invalid";
	}
}

string checkSeparator(const string &input)
{
	if (input == ";" || input == "," || input == "(" || input == ")" || input == "{" || input == "}" || input == "[" || input == "]")
	{
		return "separator " + input;
	}
	else
	{
		return "invalid";
	}
}

int main()
{
	// main logic will go here.
	ifstream myFile;
	ofstream outFile;
	Token t;

	myFile.open("Rat25f.txt");
	outFile.open("output.txt");

	while (true)
	{
		t = lexer(myFile);
		if (t.lexeme.empty())
		{
			break;
		}
	}

	for (size_t i = 0; i < t.lexeme.size(); i++)
	{
		cout << t.token[i] << " " << t.lexeme[i] << endl;
		outFile << t.token[i] << " " << t.lexeme[i] << endl;
	}

	myFile.close();
	outFile.close();

	return 0;
}