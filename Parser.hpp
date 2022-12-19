#include "scanner.hpp"
#include "SyntaxTree.hpp"

void match(string input, vector<Token> Tokens);

class Parser{
    public:
    bool error;
    SyntaxTree *outputTree = nullptr;
    Parser();
    SyntaxTree* program (vector<Token>);
    std::string draw(SyntaxTree*);
private:
    int count;
    string file;
    void drawTree(SyntaxTree*);
    SyntaxTree* stmt_sequence (vector<Token> Tokens);
    SyntaxTree* statement (vector<Token>);
    SyntaxTree* if_stmt (vector<Token> Tokens);
    SyntaxTree* repeat_stmt (vector<Token>);
    SyntaxTree* assign_stmt (vector<Token>);
    SyntaxTree* read_stmt (vector<Token> Tokens);
    SyntaxTree* write_stmt (vector<Token> Tokens);
    SyntaxTree* exp (vector<Token>);
    SyntaxTree* comparison_op (vector<Token>);
    SyntaxTree* simple_exp(vector<Token>);
    SyntaxTree* addop(vector<Token>);
    SyntaxTree* term(vector<Token>);
    SyntaxTree* mulop(vector<Token>);
    SyntaxTree* factor(vector<Token>);
    const SyntaxTree *getOutputTree() const;

};
