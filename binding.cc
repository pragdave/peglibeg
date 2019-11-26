#include "binding.h"

using namespace std;

Binding::Binding () {}

void Binding::set_variable(string& name, AstNode*& val) {
	map<string, AstNode*>::iterator it = bindings.find(name);
	if (it != bindings.end()) {
		it->second = val;
	} else {
		bindings.insert( pair<string, AstNode*>(name, val) );
	}
}

AstNode* Binding::get_variable_value(string& name) {
	return bindings.find(name)->second;
}

Binding& Binding::operator = (Binding& b) {
	this->bindings = b.bindings;
	return *this;
}

