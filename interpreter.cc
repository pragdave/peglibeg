#include <string>
#include <functional>
#include "ast_node.h"
#include "interpreter.h"


int Interpreter::evaluate_integer(AstNode *node, int value)
{
	return value;
}

int Interpreter::evaluate_binop(AstNode *node, AstNode *left, std::string op, AstNode *right)
{
	int lval = left->accept(this);
	int rval = right->accept(this);
	return eval_op[op](lval, rval);
}

int Interpreter::evaluate_varref(AstNode *node, std::string name) {
    cout << "Evaluating varref" << endl;
    return bindings.get_variable_value(name);
}

int Interpreter::evaluate_assignment(AstNode *node, std::string left, int right) {
    bindings.set_variable(left, right);
    return 1;
}


/*
int Interpreter::evaluate_if_expr(AstNode *node, int run, int e) {
	if (run == 1) {
		return evaluate_then_expr(node);
	} else (e == 1) {
		return evaluate_else_expr(node);
	}

	return 0;
};

int Interpreter::evaluate_then_expr(AstNode *node) { return 0; };
int Interpreter::evaluate_else_expr(AstNode *node) { return 0; };
*/
