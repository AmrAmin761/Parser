
#include "Parser.hpp"

unsigned int index = 0;
Token token;
bool error = false;
set<int> err;
void match(string input, vector<Token> Tokens){ 
    if(input == Tokens[index].Type){
        index++;
    }
    else{
        error = true;
        err.insert(index);
    }

}


Parser::Parser()
{
    error = false;
}

SyntaxTree* Parser::program (vector<Token> Tokens){
    SyntaxTree* node = stmt_sequence(Tokens);
     if (index < Tokens.size()) {
        error = true;
        err.insert(index);
    }
    return node;
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
        current->setSibling(statement(Tokens));
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
    else{
        error = true;
        err.insert(index);
    }
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

//comparison-op -> < | =


SyntaxTree* comparison_op (vector<Token> Tokens){
    Token x;
    if (index < Tokens.size())
        x = Tokens[index];
    SyntaxTree *current = NULL;
    if(x.Type == "LESSTHAN"){
        current = new SyntaxTree();
        current->setType(OPERATOR_EXPRESSION);
        current->setValue(Tokens[index].Value);
        match("LESSTHAN",Tokens);
    }
    else if(x.Type == "EQUAL"){
        current = new SyntaxTree();
        current->setType(OPERATOR_EXPRESSION);
        current->setValue(Tokens[index].Value);
        match("EQUAL",Tokens);
    }
    else{
        error = true;
        err.insert(index);
    }
    return current;
}

//simple-exp -> term {addop term}

SyntaxTree* simple_exp(vector<Token> Tokens){
    SyntaxTree *current, *c1 = term(Tokens), *c2;
    Token x;
    if(index<Tokens.size()){
        x=Tokens[index];
    }
    while (x.Type=="PLUS" || x.Type == "MINUS")
    {
        current = addop(Tokens);
        current->addChild(c1);
        c2 = term(Tokens);
        current->addChild(c2);
        c1 = current;
        if(index<Tokens.size()){
            x=Tokens[index];
        }
        else{
            break;
        }
    }
    return c1;
}

//addop -> + | -

SyntaxTree* addop(vector<Token> Tokens){
    Token x;
    if(index<Tokens.size()){
        x = Tokens[index];
    }
    SyntaxTree *current = NULL;
    if(x.Type == "PLUS"){
        current = new SyntaxTree();
        current->setType(OPERATOR_EXPRESSION);
        current->setValue(Tokens[index].Value);
        match("PLUS",Tokens);
    }
    else if(x.Type == "MINUS"){
        current = new SyntaxTree();
        current->setType(OPERATOR_EXPRESSION);
        current->setValue(Tokens[index].Value);
        match("MINUS",Tokens);
    }
    else{
        error = true;
        err.insert(index);
    }
    return current;
}

//term -> factor {mulop factor}

SyntaxTree* term(vector<Token> Tokens){
    SyntaxTree *current, *c1 = factor(Tokens), *c2;
    Token x;
    if(index<Tokens.size()){
        x=Tokens[index];
    }
    while (x.Type=="MULT" || x.Type == "DIV")
    {
        current = mulop(Tokens);
        current->addChild(c1);
        c2 = factor(Tokens);
        current->addChild(c2);
        c1 = current;
        if(index<Tokens.size()){
            x=Tokens[index];
        }
        else{
            break;
        }
    }
    return c1;
}

//mulop -> * | /

SyntaxTree* mulop(vector<Token> Tokens){
    Token x;
    if(index<Tokens.size()){
        x = Tokens[index];
    }
    SyntaxTree *current = NULL;
    if(x.Type == "MULT"){
        current = new SyntaxTree();
        current->setType(OPERATOR_EXPRESSION);
        current->setValue(Tokens[index].Value);
        match("MULT",Tokens);
    }
    else if(x.Type == "DIV"){
        current = new SyntaxTree();
        current->setType(OPERATOR_EXPRESSION);
        current->setValue(Tokens[index].Value);
        match("DIV",Tokens);
    }
    else{
        error = true;
        err.insert(index);
    }
    return current; 
}

//factor -> (exp) | number | identifier

SyntaxTree* factor(vector<Token> Tokens){
    Token x;
    if(index<Tokens.size()){
        x = Tokens[index];
    }
    SyntaxTree *current = NULL;
    if(x.Type == "OPENBRACKET"){
        match("OPENBRACKET",Tokens);
        current=exp(Tokens);
        match("CLOSEDBRACKET",Tokens);
    }
    else if (x.Type == "NUMBER"){
        current = new SyntaxTree();
        current->setType(CONSTANT_EXPRESSION);
        current->setValue(Tokens[index].Value);
        match("NUMBER",Tokens);
    }
    else if (x.Type == "IDENTIFIER"){
        current = new SyntaxTree();
        current->setType(IDENTIFIER_EXPRESSION);
        current->setValue(Tokens[index].Value);
        match("IDENTIFIER",Tokens);
    }
    else{
        error = true;
        err.insert(index);
    }
    return current;
}
