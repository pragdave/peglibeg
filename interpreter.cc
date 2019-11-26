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
	return ans;
}

int Interpreter::evaluate_varref(AstNode *node, string name) {
	AstNode* ans = bindings.get_variable_value(name);
	return ans->accept(this);
}

int Interpreter::evaluate_assignment(AstNode* node, AstNode* left, string op, AstNode* right) {
	string name = left->to_string();
	int value = right->accept(this);    
	bindings.set_variable(name, right);
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

int Interpreter::evaluate_block(AstNode *node, vector<AstNode*> nodes) {
	int ret = 0;
	for (int i = 0; i < nodes.size(); i++) {
		ret = nodes[i]->accept(this);
		cout << "ret " << ret << endl;
	}
	return ret;
};

int Interpreter::evaluate_funcall(AstNode *node, vector<string> names, vector<AstNode*> nodes, AstNode* block) {
	cout << "eval funccall" << endl;
	Binding b;
	cout << "after binding" << endl;
	if (names.size() != nodes.size()) {
		cout << "Err in parameters..." << endl;
		return -1;
	}
	for (int i = 0; i < names.size(); i++)  {
		cout << "setting" << endl;
		b.set_variable(names[i], nodes[i]);
		cout << "setting var done" << endl;
	}
	cout << "interp" << endl;
	Interpreter* forFunc = getInterpreter(b);
	cout << "should ret?" << endl;
	cout << block->to_string() << endl;
	
	cout << b.get_variable_value(names[0])->accept(this) << endl;
	cout << forFunc->bindings.get_variable_value(names[0])->accept(this) << endl;
	return forFunc->evaluate_block(node, block->getCode());
};

AstNode* Interpreter::find_func(string name) {
	AstNode* ans = bindings.get_variable_value(name);
	return ans;
};

Interpreter* Interpreter::getInterpreter(Binding& b) {
	Interpreter* ret = new Interpreter();
	ret->bindings = b;
	return ret;
}
