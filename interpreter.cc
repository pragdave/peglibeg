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
	int ans = eval_op[op](lval, rval);
	std::cout << "binop answer : " << ans << std::endl;
	return ans;
}

int Interpreter::evaluate_varref(AstNode *node, std::string name) {
	int ans = bindings.get_variable_value(name);
	std::cout << "varref answer : " << ans << std::endl;
	return ans;
}

int Interpreter::evaluate_assignment(AstNode* node, AstNode* left, std::string op, AstNode* right) {
	std::string name = left->to_string();
	int value = right->accept(this);    
	bindings.set_variable(name, value);
    std::cout << "assignment answer : " << value << std::endl;
	return value;
}

int Interpreter::evaluate_if_expr(AstNode *node, AstNode *left, AstNode *right, AstNode *el) {
	if (left->accept(this)) {
		return right->accept(this);
	} else if (el != nullptr) {
		return el->accept(this);
	}

	return 0;
};
