#ifndef SYNTAXTREE_H
#define SYNTAXTREE_H

#include <vector>
#include "headers.hpp"

typedef enum{
    NO_EXPRESSION,
    OPERATOR_EXPRESSION,
    CONSTANT_EXPRESSION,
    IDENTIFIER_EXPRESSION,
    ASSIGN_STATEMENT,
    IF_STATEMENT,
    REPEAT_STATEMENT,
    READ_STATEMENT,
    WRITE_STATEMENT
}NodeType;

class SyntaxTree
{
    std::vector<SyntaxTree *> children;
    SyntaxTree *sibling = nullptr;
    NodeType type = NO_EXPRESSION;
    string value = "";
public:
    SyntaxTree();

    const std::vector<SyntaxTree *> &getChildren() const;

    void addChild(SyntaxTree *child);

    bool isLeaf();

    SyntaxTree *getSibling() const;

    void setSibling(SyntaxTree *newSibling);

    bool hasSibling();

    NodeType getType() const;

    void setType(NodeType newType);

    const string &getValue() const;

    void setValue(const string &newValue);

    ~SyntaxTree();
};

#endif // SYNTAXTREE_H