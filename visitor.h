#pragma once

class AstNode;

class Visitor
{
public:
    virtual int evaluate_integer(AstNode *node, int value) { return 0;};
    virtual int evaluate_binop(AstNode *node, AstNode *left, std::string op, AstNode *right) { return 0; };
    virtual int evaluate_varref(AstNode *node, std::string name) { return 0; };
    virtual int evaluate_assignment(AstNode *node, std::string left, int right) { return 0; }; 

};
