#pragma once
#include <map>
#include <string>
#include <vector>

#include "visitor.h"
#include "binding.h"

using namespace std;

class Interpreter : public Visitor {
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
	int evaluate_binop(AstNode *node, AstNode *left, string op, AstNode *right);
	int evaluate_varref(AstNode *node, string name);
	int evaluate_assignment(AstNode* node, AstNode* left, string op, AstNode* right);
	int evaluate_if_expr(AstNode *node, AstNode *left, AstNode *right, AstNode *el);
	int evaluate_block(AstNode *node, vector<AstNode*> nodes, int numNodes);
};
