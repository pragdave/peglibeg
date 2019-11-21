#include <string>
#include <map>
#include <iostream>

class Binding {
    
    std::map<std::string, int> bindings;

    public:
	Binding();
	void set_variable(std::string, int val);
	int get_variable_value(std::string name);
};
