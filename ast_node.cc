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

Assigner::Assigner(std::string n, int val) {
    name = n;
    value = val;
}

std::string Assigner::to_string() {
    return "name : " + name + " value : " + std::to_string(value) + "\n"; 
}

int Assigner::accept(Visitor *visitor) {
    return visitor->evaluate_assignment(this, name, value);
}

////////////////////
// IfElse
/*
IfElseNode::IfElseNode() {

}

std::string IfElseNode::to_string() {
	return "hello";
}

int IfElseNode::accept(Visitor *visitor) {
	return 1;
}
*/
