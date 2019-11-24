#include <peglib.h>
#include <iostream>
#include <cstdlib>

#include "visitor.h"
#include "ast_node.h"
#include "interpreter.h"


using namespace peg;
using namespace std;

auto grammar = R"(
		program                         <-  ( statement _ )*
        statement                       <-  ( vDec 
                                        /   assignment 
                                        /   expr 
                                        /   comment)+
        vDec                            <-  'let' _ variable_declaration
        variable_declaration            <-  decl (_)? (',' (_)? decl)*
        decl                            <-  identifier (_)? '=' (_)? expr
        assignment                      <-  identifier _ '=' _ expr
        boolean_expression              <-  arithmetic_expression _ relop _ arithmetic_expression
        arithmetic_expression           <-  mult_term (_ add_op _ mult_term )*
        mult_term                       <-  primary (_ mul_op _ primary)* 
        expr                            <-  function_definition
                                        /   ifexpression
                                        /   boolean_expression 
                                        /   arithmetic_expression
        function_definition             <-  'fn' _ param_list _ block
        param_list                      <-  '(' _ identifier ( ',' _ identifier)* ')' 
                                        /   '(' _ ')'
        functioncall                    <-  'print' _ '(' _ call_arguments _ ')'
                                        /   variablereference _ '(' _ call_arguments _ ')'
        call_arguments                  <-  (_ expr _ (',' _ expr)*)?
        block                           <-  '{' (_ statement _)* '}'
        ifexpression                    <-  'if' _ expr _ block _ ('else' _ block)? _
        variablereference               <-  identifier
        primary                         <-  variablereference
                                        /   functioncall
                                        /   number
                                        /   '(' _ arithmetic_expression _ ')'
        comment                         <-  '#' [''""``-+0-9|a-zA-Z=>< ]* '\n'?
        ~_                              <-  [ \t\r\n]*
        ~__                             <-  ![a-zA-Z0-9] _
        identifier                      <-  < [a-z] >
        number                         	<-  < ('-')? [0-9]+ > 
        add_op                          <-  < '+' / '-' > 
        mul_op                          <-  < '*' / '/' > 
        relop                           <-  < '==' / '!=' / '>=' / '>' / '<=' / '<' >
    )";

class Visitor;




////////////////////
//  ParseTreeNode

class ParseTreeNode
{
    AstNode *content;

public:
    ParseTreeNode(){};
    ParseTreeNode(AstNode *content_node)
    {
        content = content_node;
    }

    AstNode *get() const
    {
        return content;
    }

    string to_string()
    {
        return content->to_string();
    }
};

AstNode *bin_op(const SemanticValues &sv)
{
    AstNode *left = sv[0].get<ParseTreeNode>().get();

    for (auto i = 1u; i < sv.size(); i += 2)
    {
        AstNode *right = sv[i + 1].get<ParseTreeNode>().get();
        string op = sv[i].get<ParseTreeNode>().get()->to_string();
        left = new BinopNode(left, op, right);

    }
    return left;
};

AstNode *assign(const SemanticValues &sv) {
	AstNode *left = sv[0].get<ParseTreeNode>().get();
	for (auto i = 1u; i < sv.size(); i += 2) {
		AstNode *right = sv[i].get<ParseTreeNode>().get();
		left = new Assigner(left, "=", right);
	}
	return left;
}

AstNode *ifElse(const SemanticValues &sv) {
	AstNode *left = sv[0].get<ParseTreeNode>().get();
	AstNode *right = sv[1u].get<ParseTreeNode>().get();
	AstNode *el = nullptr;
	if (sv.size() > 2u) {
		el = sv[2u].get<ParseTreeNode>().get();
	}
	left = new IfElseNode(left, right, el);
	return left;
}

void setup_ast_generation(parser &parser)
{

    parser["decl"] = [](const SemanticValues &sv) {
		AstNode *n = assign(sv);
		return ParseTreeNode(n);
	
    };

    parser["assignment"] = [](const SemanticValues &sv) {
		AstNode *n = assign(sv);
		return ParseTreeNode(n);
	
    };

    parser["boolean_expression"] = [](const SemanticValues &sv) {
		AstNode *n = bin_op(sv);
		return ParseTreeNode(n);
	
    };

    parser["arithmetic_expression"] = [](const SemanticValues &sv) {
		AstNode *n = bin_op(sv);
		return ParseTreeNode(n);
	
    };

    parser["mult_term"] = [](const SemanticValues &sv) {
		AstNode *n = bin_op(sv);
		return ParseTreeNode(n);
	
    };

    /*parser["function_definition"] = [](const SemanticValues &sv) {
	would remove fn and things maybe?
	
    };*/

    /*parser["param_list"] = [](const SemanticValues &sv) {
	run through all identifiers?
	
    };*/

    /*parser["functioncall"] = [](const SemanticValues &sv) {
	run function using call arguments
	
    };*/

    /*parser["call_arguments"] = [](const SemanticValues &sv) {
	bind values to function name values in new scope
	
    };*/

    /*parser["block"] = [](const SemanticValues &sv) {
		ParseTreeNode n = ParseTreeNode();
		n.get()->accept(new Interpreter());
		return n;

    };*/

    parser["ifexpression"] = [](const SemanticValues &sv) {
		AstNode *n = ifElse(sv);
		return ParseTreeNode(n);

    };

	parser["identifier"] = [](const SemanticValues &sv) {
		return ParseTreeNode(new VariableValue(sv.str()));
	};

    parser["variablereference"] = [](const SemanticValues &sv) {
		return ParseTreeNode(new VariableValue(sv.str()));
    };

    parser["number"] = [](const SemanticValues &sv) {
        return ParseTreeNode(new IntegerNode(atoi(sv.c_str())));
    };

    parser["add_op"] = [](const SemanticValues &sv) {
        return ParseTreeNode(new OpNode(sv.str()));
    };

    parser["mul_op"] = [](const SemanticValues &sv) {
        return ParseTreeNode(new OpNode(sv.str()));
    };

    parser["relop"] = [](const SemanticValues &sv) {
		return ParseTreeNode(new OpNode(sv.str()));
    };
}

int main(int argc, const char **argv)
{
    if (argc < 2 || string("--help") == argv[1])
    {
        cout << "usage: parser [formula]" << endl;
        return 1;
    }

    parser parser(grammar);
    setup_ast_generation(parser);


    ParseTreeNode val = ParseTreeNode();
	Interpreter* I = new Interpreter();
	for (int i = 1; i < argc; i++) {
		auto expr = argv[i];
		if (parser.parse(expr, val)) {
			cout << val.get()->accept(I) << " is the final answer." << endl;
		} else {
			cout << "syntax error..." << endl;
			return -1;
		}
	}


}
