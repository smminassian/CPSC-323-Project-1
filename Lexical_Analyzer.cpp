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
    string line;
    cout << "Starting lexical analysis..." << endl;

    string current_lexeme = "";

    while (getline(myFile, line))
    {
        for (char ch : line)
        {
            if (checkSeparator(string(1, ch)) != "invalid" || checkOperator(string(1, ch)) != "invalid")
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

	if (state == IdValid || state == IdInvalid)
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
		return "integer ";
	}
	else if (state == NumReal)
	{
		return "real ";
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
		return "keyword ";
	}
	else
	{
		return "identifier ";
	}
}

string checkOperator(const string &input)
{
	if (input == "+" || input == "-" || input == "*" || input == "/" || input == "<=" || input == ">=" || input == "=" || input == "<" || input == ">" || input == "!=")
	{
		return "operator ";
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
		return "separator ";
	}
	else
	{
		return "invalid";
	}
}

int main()
{
    // Input and output filenames
    vector<string> inputFiles = { "Rat25f.txt", "Rat25f2.txt", "Rat25f3.txt" };
    vector<string> outputFiles = { "output.txt", "output2.txt", "output3.txt" };

    // Making sure the vectors match in size
    if (inputFiles.size() != outputFiles.size())
    {
        cerr << "Error: Input and output file lists do not match in size." << endl;
        return 1;
    }

    for (size_t i = 0; i < inputFiles.size(); i++)
    {
        ifstream myFile(inputFiles[i]);
        ofstream outFile(outputFiles[i]);

        if (!myFile)
        {
            cerr << "Error opening input file: " << inputFiles[i] << endl;
            continue; 
        }

        if (!outFile)
        {
            cerr << "Error opening output file: " << outputFiles[i] << endl;
            myFile.close();
            continue;
        }

        cout << "Processing " << inputFiles[i] << " -> " << outputFiles[i] << endl;

        Token t = lexer(myFile);

        for (size_t j = 0; j < t.lexeme.size(); j++)
        {
            outFile << t.token[j] << " " << t.lexeme[j] << endl;
            cout << t.token[j] << " " << t.lexeme[j] << endl;
        }

        myFile.close();
        outFile.close();
    }

    return 0;
}
