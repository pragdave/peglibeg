#pragma once
#include <map>
#include <string>

#include "visitor.h"

using namespace std;

class Interpreter : public Visitor
{
    map<string, function<int(int, int)>> eval_op = {
        {"+", [](int l, int r) { return l + r; }},
        {"-", [](int l, int r) { return l - r; }},
        {"*", [](int l, int r) { return l * r; }},
        {"/", [](int l, int r) { return l / r; }},
	{"==", [](int l, int r) { return l == r; }},
	{"!=", [](int l, int r) { return l != r; }},
        {">=", [](int l, int r) { return l>= r; }},
	{">", [](int l, int r) { return l > r; }},
	{"<=", [](int l, int r) { return l <= r; }},
	{"<", [](int l, int r) { return l < r; }}};

public:
    int evaluate_integer(AstNode *node, int value);
    int evaluate_binop(AstNode *node, AstNode *left, std::string op, AstNode *right);
};
