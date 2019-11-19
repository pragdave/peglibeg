#pragma once
#include <map>
#include <string>

#include "visitor.h"

class Interpreter : public Visitor
{
    std::map<std::string, std::function<int(int, int)>> eval_op = {
        {"+", [](int l, int r) { return l + r; }},
        {"-", [](int l, int r) { return l - r; }},
        {"*", [](int l, int r) { return l * r; }},
        {"/", [](int l, int r) { return l / r; }}};

public:
    int evaluate_integer(AstNode *node, int value);
    int evaluate_binop(AstNode *node, AstNode *left, std::string op, AstNode *right);
};
