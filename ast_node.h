#pragma once

#include <string>
#include <vector>

#include "visitor.h"

using namespace std;

class AstNode {
public:
	virtual string to_string() { return string("node"); };
	virtual int accept(Visitor *visitor) { return 99999; }
};



////////////////////
//  IntegerNode

class IntegerNode : public AstNode {
	int value;
public:
	IntegerNode(int given);
	string to_string();
	int accept(Visitor *visitor);
};

////////////////////
//  BinopNode

class BinopNode : public AstNode {
	AstNode *left;
	string op;
	AstNode *right;
public:
	BinopNode(AstNode *pleft, string pop, AstNode *pright);
	string to_string();
	int accept(Visitor *visitor);
};

////////////////////
//  OpNode

class OpNode : public AstNode {
	string op;
public:
	OpNode(string pop);
	string to_string();
	int accept(Visitor *visitor);
};

////////////////////
//  VariableValue

class VariableValue : public AstNode {
	string name;
public:
	VariableValue(string n);
	string to_string();
	int accept(Visitor *visitor);
};

////////////////////
//  Assigner

class Assigner : public AstNode {
	AstNode *left;
	string op;
	AstNode *right;
public:
	Assigner(AstNode *pleft, string op, AstNode *pright);
	string to_string();
	int accept(Visitor *visitor);
};

////////////////////
// IfElse

class IfElseNode : public AstNode {
	AstNode *left;
	AstNode *right;
	AstNode *el;
public:
	IfElseNode(AstNode *pleft, AstNode *pright, AstNode *pel);
	string to_string();
	int accept(Visitor *visitor);
};

////////////////////
// Block

class Block : public AstNode {
	vector<AstNode*> nodes;
	int numNodes;
public:
	Block(vector<AstNode*> ns, int nN);
	string to_string();
	int accept(Visitor *visitor);
};

