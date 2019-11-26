#include <sstream>
#include <iterator>

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
	return "( " + left->to_string() + op + right->to_string() + " )";
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
	string ret = "( " + left->to_string() + " : " + right->to_string();
	if (el != nullptr)
		ret = ret + " : " + el->to_string() + "\n";
	ret = ret + " )";
	return ret;
}

int IfElseNode::accept(Visitor *visitor) {
	return visitor->evaluate_if_expr(this, left, right, el);
}

////////////////////
// Block

Block::Block(vector<AstNode*> ns, int nN) {
	nodes = ns;
	numNodes = nN;
}

string Block::to_string() {
	//string ret = "";
	for (int i = 0; i < numNodes; i++) {
	//	ret = nodes[i]->to_string();

	}
	return "block";
}

int Block::accept(Visitor *visitor) {
	return visitor->evaluate_block(this, nodes);
}

vector<AstNode*> Block::getCode() {
	return nodes;
}

////////////////////
// FunCall

FunCall::FunCall(vector<AstNode*> v, AstNode* funcD) {
	block = funcD;
	vars = v;
}

string FunCall::to_string() {
	return "hi";
}

int FunCall::accept(Visitor *visitor) {
	AstNode* funcD = visitor->find_func(block->to_string());

	stringstream ss(funcD->to_string());
	istream_iterator<string> begin(ss);
	istream_iterator<string> end;
	vector<string> vstrings(begin, end);

	return visitor->evaluate_funcall(this, vstrings, vars, funcD->getBlock());
}

////////////////////
// FunDef

FunDef::FunDef(AstNode* b, vector<AstNode*> v) {
	block = b;
	vars = v;
}

string FunDef::to_string() {
	string ret = "";
	for (int i = 0; i < vars.size(); i++) {
		ret = ret + vars[i]->to_string() + " ";
	}
	return ret;
}

int FunDef::accept(Visitor *visitor) {
	return 0;
}

AstNode* FunDef::getBlock() {
	return block;
}
