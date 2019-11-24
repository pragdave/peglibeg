#include "ast_node.h"


////////////////////
//  IntegerNode

IntegerNode::IntegerNode(int given)
{
  value = given;
}

std::string IntegerNode::to_string()
{
  return std::to_string(value);
}

int IntegerNode::accept(Visitor *visitor)
{
  return visitor->evaluate_integer(this, value);
}

////////////////////
//  BinopNode

BinopNode::BinopNode(AstNode *pleft, std::string pop, AstNode *pright)
{
  left = pleft;
  op = pop;
  right = pright;
}

int BinopNode::accept(Visitor *visitor)
{
  return visitor->evaluate_binop(this, left, op, right);
}

std::string BinopNode::to_string()
{
  return "(" + left->to_string() + op + right->to_string() + ")";
}

////////////////////
//  OpNode

OpNode::OpNode(std::string pop)
{
  op = pop;
}

int OpNode::accept(Visitor *visitor) {
  return 0;  // never called.
}

std::string OpNode::to_string()
{
  return op;
}

////////////////////
//  VariableValue

VariableValue::VariableValue(std::string n) {
    name = n;
} 

std::string VariableValue::to_string() {
    return name;
}

int VariableValue::accept(Visitor *visitor) {
    return visitor->evaluate_varref(this, name);
}

////////////////////
//  Assigner

Assigner::Assigner(AstNode *pleft, std::string op, AstNode *pright) {
    left = pleft;
	op = op;
	right = pright;
}

std::string Assigner::to_string() {
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

std::string IfElseNode::to_string() {
	std::string ret = "if is : " + left->to_string() + " code is : " + right->to_string();
	if (el != nullptr)
		ret = ret + " else is : " + el->to_string() + "\n";
	return ret;
}

int IfElseNode::accept(Visitor *visitor) {
	return visitor->evaluate_if_expr(this, left, right, el);
}

