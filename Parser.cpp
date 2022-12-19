
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

SyntaxTree* Parser::program (vector<Token> Tokens){
    SyntaxTree* node = stmt_sequence(Tokens);
    return node;
}

SyntaxTree* statement (vector<Token> Tokens){
    SyntaxTree* node = NULL;
    Token current_token;
    if(index < Tokens.size())
        current_token = Tokens[index];
    if( current_token.Type == "IF" ){
        node = if_stmt(Tokens);
    } else if(current_token.Type == "IDENTIFIER"){
        node = assign_stmt(Tokens);
    } else if (current_token.Type == "READ")
        node = read_stmt(Tokens);
    else if (current_token.Type == "WRITE")
        node = write_stmt(Tokens);

    return node;
}

SyntaxTree* repeat_stmt (vector<Token> Tokens){
    SyntaxTree* node = new SyntaxTree();
    match("REPEAT", Tokens);
    node->setType(REPEAT_STATEMENT);
    node->addChild(stmt_sequence(Tokens));
    match("UNTIL", Tokens);
    node->addChild(exp(Tokens));
    return node;
}

SyntaxTree* assign_stmt (vector<Token> Tokens){
    SyntaxTree* node = new SyntaxTree();
    node->setType(ASSIGN_STATEMENT);
    match("IDENTIFIER",Tokens);
    match("ASSIGN", Tokens);
    node->addChild(exp(Tokens));
    return node;
}

SyntaxTree* exp (vector<Token> Tokens){
    SyntaxTree* cur, *c1 = simple_exp(Tokens), *c2;
    Token x;
    if (index < Tokens.size())
        x = Tokens[index];
    if (x.Type == "LESSTHAN" || x.Type == "EQUAL") {
        cur = comparison_op(Tokens);
        cur->addChild(c1);
        c2 = simple_exp(Tokens);
        cur->addChild(c2);
        c1 = cur;
    }
    return c1;
}

