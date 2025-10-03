#include <iostream>
#include <string>
#include <fstream>
using namespace std;


int lexer(char* token){
    // Implement lexical analysis here. We return lexeme and token later
    return 0;
}


int main(){
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