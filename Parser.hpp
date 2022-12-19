#include "scanner.hpp"
#include "SyntaxTree.hpp"

void match(string input, vector<Token>  Tokens);

class Parser{
    public:
    bool error;
    SyntaxTree *outputTree = nullptr;
    Parser();
    SyntaxTree* program (vector<Token> Tokens);
    std::string draw(SyntaxTree*);
private:
    int count;
    string file;
    void drawTree(SyntaxTree*);
    SyntaxTree* stmt_sequence (vector<Token>  Tokens);
    SyntaxTree* statement (vector<Token> Tokens);
    SyntaxTree* if_stmt (vector<Token> Tokens);
    SyntaxTree* repeat_stmt (vector<Token> Tokens);
    SyntaxTree* assign_stmt (vector<Token> Tokens);
    SyntaxTree* read_stmt (vector<Token> Tokens);
    SyntaxTree* write_stmt (vector<Token> Tokens);
    SyntaxTree* exp (vector<Token> Tokens);
    SyntaxTree* comparison_op (vector<Token> Tokens);
    SyntaxTree* simple_exp(vector<Token> Tokens);
    SyntaxTree* addop(vector<Token> Tokens);
    SyntaxTree* term(vector<Token> Tokens);
    SyntaxTree* mulop(vector<Token> Tokens);
    SyntaxTree* factor(vector<Token> Tokens);
    const SyntaxTree *getOutputTree() const;

};
