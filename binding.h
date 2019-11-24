#include <string>
#include <map>
#include <iostream>

using namespace std;

class Binding {
	map<string, int> bindings;
public:
	Binding();
	void set_variable(string, int val);
	int get_variable_value(string name);
};
