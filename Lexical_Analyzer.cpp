#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
using namespace std;


int lexer(char* token){
    // Implement lexical analysis here. We return lexeme and token later
    return 0;
}

const int IdBeginning = 0;
const int IdValid = 1;
const int IdInvalid = 2;

string IdentifierFSM (const string& input){
	int state = IdBeginning;
	
	for (size_t  i = 0; i < input.size(); i++){
		char ch = input[i];
		
		switch (state) {
			case IdBeginning:
			if (isalpha(ch) == true) {
				state = IdValid;
			} else {
				state = IdInvalid;
			}
			break;
				
			case IdValid:
			if (isalnum(ch) == true) {
				state = IdValid;
			} else {
				state = IdInvalid;
			}
			break;
				
			case IdInvalid:
				break;
		}
		if (state == IdInvalid) {break;}
	}
	
	if (state == IdValid) {
		return "identifier " + input;
	} else { return "invalid"; }
		
	
}

const int NumBeginning = 0;
const int NumInt = 1;
const int NumReal = 2;
const int NumInvalid = 3;

string NumberFSM (const string& input){
	int state = NumBeginning;
	
	for (size_t  i = 0; i < input.size(); i++){
		char ch = input[i];
		
		switch (state) {
			case NumBeginning:
			if (isnum(ch) == true) {
				state = NumInt;
			} else if (ch == ".") {
				state = NumReal;
			} else {
				state = NumInvalid;
			}
			break;
				
			case NumInt:
			if (isnum(ch) == true) {
				state = NumInt;
			} else if (ch == ".") {
				state = NumReal;
			} else {
				state = NumInvalid;
			}
			break;
			
			case NumReal:
			if (isnum(ch) == true) {
				state = NumReal;
			} else {
				state = NumInvalid;
			}
			
			case NumInvalid:
				break;
		}
		if (state == NumInvalid) {break;}
	}
	
	if (state == NumInt) {
		return "integer " + input;
	} else if (state == NumReal) {
		return "real " + input;
	} else { return "invalid"; }
		
	
}


int main(int argc, char* argv[]){
   //main logic will go here. 

    ifstream myfile;
    myfile.open("Rat25f.txt");
    if(!myfile){
        cout<<"File not found"<<endl;
        return -1;
    }
    while(!myfile.eof()){
        char token[20];
        char lexeme[20];
        lexer(token);
        cout<<token<<" "<<lexeme<<endl;
    }

   return 0;
}
