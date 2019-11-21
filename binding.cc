#include "binding.h"

Binding::Binding () {
	bindings.insert( std::pair<std::string, int>("x", 5) );
}

void Binding::set_variable(std::string name, int val) {
	if (bindings.find(name)->second) {
		bindings.find(name)->second = val;
	} else {
    	bindings.insert( std::pair<std::string, int>(name, val) );
	}
}

int Binding::get_variable_value(std::string name) {
    return bindings.find(name)->second;
}
