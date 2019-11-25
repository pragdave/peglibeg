#include <string>
#include <functional>

#include "ast_node.h"
#include "interpreter.h"

using namespace std;

int Interpreter::evaluate_integer(AstNode *node, int value) {
	return value;
}

int Interpreter::evaluate_binop(AstNode *node, AstNode *left, string op, AstNode *right) {
	int lval = left->accept(this);
	int rval = right->accept(this);
	int ans = eval_op[op](lval, rval);
	//cout << "Binop is " << to_string(ans) << endl;
	return ans;
}

int Interpreter::evaluate_varref(AstNode *node, string name) {
	int ans = bindings.get_variable_value(name);
	//cout << "Varref is " << to_string(ans) << endl;
	return ans;
}

int Interpreter::evaluate_assignment(AstNode* node, AstNode* left, string op, AstNode* right) {
	string name = left->to_string();
	int value = right->accept(this);    
	bindings.set_variable(name, value);
	//cout << "Assignment is " << to_string(value) << endl;
	return value;
}

int Interpreter::evaluate_if_expr(AstNode *node, AstNode *left, AstNode *right, AstNode *el) {
	//cout << "If expr " << endl;
	if (left->accept(this)) {
		return right->accept(this);
	} else if (el != nullptr) {
		return el->accept(this);
	}
	return 0;
};

int Interpreter::evaluate_block(AstNode *node, vector<AstNode*> nodes, int numNodes) {
	int ret = 0;
	for (int i = 0; i < numNodes; i++) {
		ret = nodes[i]->accept(this);
		cout << ret << endl;
	}
	return ret;
};

