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
