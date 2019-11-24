#include "binding.h"

using namespace std;

Binding::Binding () {
	bindings.insert( pair<string, int>("x", 5) );
}

void Binding::set_variable(string name, int val) {
	map<string, int>::iterator it = bindings.find(name);
	if (it != bindings.end()) {
		it->second = val;
	} else {
		bindings.insert( pair<string, int>(name, val) );
	}
}

int Binding::get_variable_value(string name) {
	return bindings.find(name)->second;
}
