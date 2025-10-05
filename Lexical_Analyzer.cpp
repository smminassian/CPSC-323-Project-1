#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
using namespace std;

struct Token
{
	char token[20];
	char lexeme[20];
};

Token lexer(ifstream &myFile)
{
	Token t;
	char ch;
	int ix = 0;

	while (myFile.get(ch))
	{
		if (ch == ' ' || ch == '\n' || ch == '\t')
		{
			t.lexeme[ix] = '\0';
			//call FSM functions here
			
			continue;
			ix = 0;
		}
		t.lexeme[ix] = ch;
		ix++;
	}
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
				if (isnum(ch) == true)
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
				if (isnum(ch) == true)
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

	int main()
	{
		// main logic will go here.
		ifstream myFile;
		Token t;

		while (!myFile.eof())
		{
			t = lexer(myFile);
			cout << "<" << t.token << ", " << t.lexeme << ">" << endl;
		}

		return 0;
	}