#pragma once
#include <map>
#include <string>

#include "visitor.h"
#include "binding.h"

using namespace std;

class Interpreter : public Visitor
{
    map<string, function<int(int, int)>> eval_op = {
        {"+",  [] (int l, int r) { return l + r;  }},
        {"-",  [] (int l, int r) { return l - r;  }},
        {"*",  [] (int l, int r) { return l * r;  }},
        {"/",  [] (int l, int r) { return l / r;  }},
	{"==", [] (int l, int r) { return l == r; }},
	{"!=", [] (int l, int r) { return l != r; }},
        {">=", [] (int l, int r) { return l>= r;  }},
	{">",  [] (int l, int r) { return l > r;  }},
	{"<=", [] (int l, int r) { return l <= r; }},
	{"<",  [] (int l, int r) { return l < r;  }}};

    Binding bindings;

public:
    int evaluate_integer(AstNode *node, int value);
    int evaluate_binop(AstNode *node, AstNode *left, std::string op, AstNode *right);
    int evaluate_varref(AstNode *node, std::string name);
    int evaluate_assignment(AstNode *node, std::string left, int right);

    //int evaluate_if_expr(AstNode *node, int run, int e) { return 0; };
    //int evaluate_then_expr(AstNode *node) { return 0; };
    //int evaluate_else_expr(AstNode *node) { return 0; };
};


