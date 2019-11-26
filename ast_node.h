#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "visitor.h"

using namespace std;

class AstNode {
public:
	virtual string to_string() { return string("node"); };
	virtual int accept(Visitor *visitor) { return 99999; };
	virtual AstNode* getBlock() { return 0; };
	virtual vector<AstNode*> getCode() { AstNode* temp = nullptr; vector<AstNode*> t;
						t.push_back(temp); return t; };
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
	AstNode* temp;
	vector<AstNode*> nodes;
	int numNodes;
public:
	Block(vector<AstNode*> ns, int nN);
	string to_string();
	int accept(Visitor *visitor);
	vector<AstNode*> getCode();
};

////////////////////
// FunCall

class FunCall : public AstNode {
	AstNode *block;
	vector<AstNode*> vars;
	string ref;
public:
	FunCall(vector<AstNode*> v, AstNode* b);
	string to_string();
	int accept(Visitor *visitor);
};

////////////////////
// FunDef

class FunDef : public AstNode {
	AstNode *block;
	vector<AstNode*> vars;
public:
	FunDef(AstNode* b, vector<AstNode*> v);
	string to_string();
	int accept(Visitor *visitor);
	AstNode* getBlock();
};
