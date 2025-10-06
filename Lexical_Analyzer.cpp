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

	while (myFile.get(ch))
	{

		if (checkSeparator(string(1, ch)) != "invalid" || checkOperator(string(1, ch)) != "invalid")
		{
			if (!current_lexeme.empty())
			{
				if (checkKeyword(current_lexeme) != "identifier")
				{
					t.lexeme.push_back(current_lexeme);
					t.token.push_back(checkKeyword(current_lexeme));
				}
				else if (isalpha(current_lexeme[0]))
				{
					t.lexeme.push_back(current_lexeme);
					t.token.push_back(IdentifierFSM(current_lexeme));
				}
				else if (isdigit(current_lexeme[0]))
				{
					t.lexeme.push_back(current_lexeme);
					t.token.push_back(NumberFSM(current_lexeme));
				}
				else
				{
					t.lexeme.push_back(current_lexeme);
					t.token.push_back("invalid");
				}
				current_lexeme.clear();
			}

			string op(1, ch);
			if (checkOperator(op) != "invalid")
			{
				t.lexeme.push_back(op);
				t.token.push_back(checkOperator(op));
			}
			else if (checkSeparator(op) != "invalid")
			{
				t.lexeme.push_back(op);
				t.token.push_back(checkSeparator(op));
			}
			continue;
		}

		if (isspace(ch))
		{
			if (!current_lexeme.empty())
			{
				if (checkKeyword(current_lexeme) != "identifier ")
				{
					t.lexeme.push_back(current_lexeme);
					t.token.push_back(checkKeyword(current_lexeme));
				}
				else if (isalpha(current_lexeme[0]))
				{
					t.lexeme.push_back(current_lexeme);
					t.token.push_back(IdentifierFSM(current_lexeme));
				}
				else if (isdigit(current_lexeme[0]))
				{
					t.lexeme.push_back(current_lexeme);
					t.token.push_back(NumberFSM(current_lexeme));
				}
				else
				{
					t.lexeme.push_back(current_lexeme);
					t.token.push_back("invalid");
				}
				current_lexeme.clear();
			}
			continue;
		}

		current_lexeme += ch;
	}

	if (!current_lexeme.empty())
	{
		if (checkKeyword(current_lexeme) != "identifier " + current_lexeme)
		{
			t.lexeme.push_back(current_lexeme);
			t.token.push_back(checkKeyword(current_lexeme));
		}
		else if (isalpha(current_lexeme[0]))
		{
			t.lexeme.push_back(current_lexeme);
			t.token.push_back(IdentifierFSM(current_lexeme));
		}
		else if (isdigit(current_lexeme[0]))
		{
			t.lexeme.push_back(current_lexeme);
			t.token.push_back(NumberFSM(current_lexeme));
		}
		else
		{
			t.lexeme.push_back(current_lexeme);
			t.token.push_back("invalid");
		}
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
			if (isalpha(ch) == true || ch == '_')
			{
				state = IdValid;
			}
			else
			{
				state = IdInvalid;
			}
			break;

		case IdValid:
			if (isalnum(ch) == true || ch == '_')
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
		return "identifier";
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
	if (input == "if" || input == "then" || input == "else" || input == "end" || input == "repeat" || input == "until" || input == "read" || input == "write" || input == "begin" || input == "while")
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
	if (input == "+" || input == "-" || input == "*" || input == "/" || input == "<=" || input == ">=" || input == "=" || input == "<" || input == ">" || input == "!=")
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
	Token t; // contains two vectors: token and lexeme
	

	myFile.open("Rat25f.txt");
	outFile.open("output.txt");
	if (!myFile)
	{
		cerr << "Error opening input file" << endl;
		return 1;
	}
	if (!outFile)
	{
		cerr << "Error opening output file" << endl;
		return 1;
	}

	//This line bascially passeses the whole file to the lexer function. The output of the lexer is store in t
	t = lexer(myFile);

	// Print the contents of the token and lexeme vectors to the console and to the output file
	for (size_t i = 0; i < t.lexeme.size(); i++)
	{
		outFile << t.token[i] << " " << t.lexeme[i] << endl;
		cout << t.token[i] << " " << t.lexeme[i] << endl;
	}

	myFile.close();
	outFile.close();

	return 0;
}
