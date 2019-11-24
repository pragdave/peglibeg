#include "ast_node.h"

using namespace std;

////////////////////
//  IntegerNode

IntegerNode::IntegerNode(int given) {
	value = given;
}

string IntegerNode::to_string() {
	return to_string();
}

int IntegerNode::accept(Visitor *visitor) {
	return visitor->evaluate_integer(this, value);
}

////////////////////
//  BinopNode

BinopNode::BinopNode(AstNode *pleft, string pop, AstNode *pright) {
	left = pleft;
	op = pop;
	right = pright;
}

string BinopNode::to_string() {
	return "(" + left->to_string() + op + right->to_string() + ")";
}

int BinopNode::accept(Visitor *visitor) {
	return visitor->evaluate_binop(this, left, op, right);
}

////////////////////
//  OpNode

OpNode::OpNode(string pop) {
	op = pop;
}

string OpNode::to_string() {
	return op;
}

int OpNode::accept(Visitor *visitor) {
	return 0;  // never called.
}

////////////////////
//  VariableValue

VariableValue::VariableValue(string n) {
	name = n;
} 

string VariableValue::to_string() {
	return name;
}

int VariableValue::accept(Visitor *visitor) {
	return visitor->evaluate_varref(this, name);
}

////////////////////
//  Assigner

Assigner::Assigner(AstNode *pleft, string op, AstNode *pright) {
	left = pleft;
	op = op;
	right = pright;
}

string Assigner::to_string() {
	return "(" + left->to_string() + op + right->to_string() + ")";
}

int Assigner::accept(Visitor *visitor) {
	return visitor->evaluate_assignment(this, left, op, right);
}

////////////////////
// IfElse

IfElseNode::IfElseNode(AstNode *pleft, AstNode *pright, AstNode *pel) {
	left = pleft;
	right = pright;
	el = pel;
}

string IfElseNode::to_string() {
	string ret = "if is : " + left->to_string() + " code is : " + right->to_string();
	if (el != nullptr)
		ret = ret + " else is : " + el->to_string() + "\n";
	return ret;
}

int IfElseNode::accept(Visitor *visitor) {
	return visitor->evaluate_if_expr(this, left, right, el);
}

