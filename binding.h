#include <string>
#include <map>
#include <iostream>

#include "ast_node.h"

using namespace std;

class Binding {
	map<string, AstNode*> bindings;
public:
	Binding();
	void set_variable(string&, AstNode*& val);
	AstNode* get_variable_value(string& name);
	Binding& operator=(Binding& b);
};
