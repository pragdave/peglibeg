#pragma once

#include <string>
#include "visitor.h"

class AstNode
{
public:
    virtual std::string to_string() { return std::string("node"); };
    virtual int accept(Visitor *visitor) { return 99999; }
};



////////////////////
//  IntegerNode

class IntegerNode : public AstNode
{
    int value;

public:
    IntegerNode(int given);
    std::string to_string();
    int accept(Visitor *visitor);
};

////////////////////
//  BinopNode

class BinopNode : public AstNode
{
    AstNode *left;
    std::string op;
    AstNode *right;

public:
    BinopNode(AstNode *pleft, std::string pop, AstNode *pright);
    std::string to_string();
    int accept(Visitor *visitor);
};

////////////////////
//  OpNode

class OpNode : public AstNode
{
    std::string op;

public:
    OpNode(std::string pop);
    std::string to_string();
    int accept(Visitor *visitor);
};
