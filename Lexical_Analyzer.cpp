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
		if (isspace(ch))
		{
			if (isalpha(current_lexeme[0]))
			{
				//I push the current lexeme to the lexeme vector 
				t.lexeme.push_back(current_lexeme);
				
				t.token.push_back(IdentifierFSM(current_lexeme)); // I check if it is a identifier 

				if (checkKeyword(current_lexeme) != "identifier " + current_lexeme) //if it aint a identfier i check if it is a keyword
				{
					t.token.push_back(checkKeyword(current_lexeme)); // go to keyword function
				}

				current_lexeme.clear(); // clear the current lexeme so i can start a new one
				continue;
			}
			else if (isdigit(current_lexeme[0]))  //if the current lexeme starts with a digit
			{
				t.lexeme.push_back(current_lexeme); // we push the current lexeme to the lexeme vector
				
				t.token.push_back(NumberFSM(current_lexeme)); // we check if it is a number or not 
			

				current_lexeme.clear(); // we clear the current lexeme so we can start a new one
				continue;
			}
			else if (checkOperator(current_lexeme) != "invalid") // we check if it is an operator
			{
				t.lexeme.push_back(current_lexeme); // we push the current lexeme to the lexeme vector
				t.token.push_back(checkOperator(current_lexeme)); //we go to the operator function
				current_lexeme.clear(); // we clear the current lexeme so we can start a new one
				continue;
			}
			else if (checkSeparator(current_lexeme) != "invalid") // we check if it is a separator
			{
				t.lexeme.push_back(current_lexeme); // we push the current lexeme to the lexeme vector
				t.token.push_back(checkSeparator(current_lexeme)); // we go to the separator function
				current_lexeme.clear(); // we clear the current lexeme so we can start a new one
				continue;
			}
			else
			{
				if (current_lexeme != "") // if the current lexeme is not empty
				{
					t.lexeme.push_back(current_lexeme); // we push the current lexeme to the lexeme vector
					t.token.push_back("invalid"); // we push invalid to the token vector
					current_lexeme.clear(); // we clear the current lexeme so we can start a new one
				}
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

	//While the file is open, keep calling the lexer function until the ened of the file is reached
	while (true)
	{
		t = lexer(myFile);
		if (myFile.eof())
		{
			break;
		}
	}

	//Print the contents of the token and lexeme vectors to the console and to the output file
	for (size_t i = 0; i < t.lexeme.size(); i++)
	{
		cout << t.token[i] << " " << t.lexeme[i] << endl;
		outFile << t.token[i] << " " << t.lexeme[i] << endl;
	}

	myFile.close();
	outFile.close();

	return 0;
}