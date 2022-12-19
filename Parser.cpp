#include "Parser.hpp"

unsigned int index = 0;
Token token;
bool error = false;
set<int> err;
void match(string input, vector<Token> Tokens){//needs to be refactored 
    if(input == Tokens[index].Type){
        index++;
    }
    else
        error = true;

}

