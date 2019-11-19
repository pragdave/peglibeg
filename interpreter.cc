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
