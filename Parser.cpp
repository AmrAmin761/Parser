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

SyntaxTree* stmt_sequence (vector<Token> Tokens){
    SyntaxTree *seq = new SyntaxTree();
    seq = statement(Tokens);
    SyntaxTree *current = new SyntaxTree();
    current = seq;
    Token x;
    if(index < Tokens.size()){
        x = Tokens[index];
    }
    while (x.Type == "SEMICOLON" && index != Tokens.size()-1){
        match("SEMICOLON",Tokens);
        current->getSibling(statement(Tokens));
        current = current->getSibling();
        if(index<Tokens.size()){
            x = Tokens[index];
        }
        else
            break;
    }
    return seq;
}

//if -stmt -> if exp then stmt-sequence [else statment] end

SyntaxTree* if_stmt (vector<Token> Tokens){
    SyntaxTree *current = new SyntaxTree();
    current->setType(IF_STATEMENT);
    match("IF",Tokens);
    current->addChild(exp(Tokens));
    match("THEN",Tokens);
    current->addChild(stmt_sequence(Tokens));
    Token x;
    if(index<Tokens.size()){
        x = Tokens[index];
    }
    if(x.Type == "ELSE"){
        match("ELSE",Tokens);
        current->addChild(stmt_sequence(Tokens));
    }
    match("END ",Tokens);
    return current;
}

//read -stmt -> read identifier

SyntaxTree* read_stmt (vector<Token> Tokens){
    match("READ",Tokens);
    SyntaxTree *current = new SyntaxTree();
    current->setType(READ_STATEMENT);
    current->setValue(Tokens[index].Value);
    match("IDENTIFIER",Tokens);
    return current;
}

//write -stmt -> write exp

SyntaxTree* write_stmt (vector<Token> Tokens){
    SyntaxTree *current= new SyntaxTree();
    current->setType(WRITE_STATEMENT);
    match("WRITE",Tokens);
    current->addChild(exp(Tokens));
    return current;
}