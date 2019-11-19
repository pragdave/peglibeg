#include <peglib.h>
#include <iostream>
#include <cstdlib>

#include "visitor.h"
#include "ast_node.h"
#include "interpreter.h"

using namespace peg;
using namespace std;

auto grammar = R"(
        program <-  expr+
        expr    <-  term ( add_op _ term )*
        term    <-  primary ( mul_op _ primary )*
        primary <-  number / '(' _ expr ')' _
        add_op  <-  '+' / '-'
        mul_op  <-  '*' / '/'
        number  <-  < [0-9]+ > _
        ~_      <-  [ \t\r\n]*
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

void setup_ast_generation(parser &parser)
{
    parser["expr"] = [](const SemanticValues &sv) {
        cout << "expr: " << sv.str() << endl;
        AstNode *n = bin_op(sv);
        return ParseTreeNode(n);
    };

    parser["add_op"] = [](const SemanticValues &sv) {
        return ParseTreeNode(new OpNode(sv.str()));
    };

    parser["mul_op"] = [](const SemanticValues &sv) {
        return ParseTreeNode(new OpNode(sv.str()));
    };

    parser["term"] = [](const SemanticValues &sv) {
        AstNode *n = bin_op(sv);
        return ParseTreeNode(n);
    };

    parser["number"] = [](const SemanticValues &sv) {
        return ParseTreeNode(new IntegerNode(atoi(sv.c_str())));
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

    auto expr = argv[1];
    ParseTreeNode val = ParseTreeNode();
    if (parser.parse(expr, val))
    {
        cout << val.to_string() << " = " << val.get()->accept(new Interpreter()) << endl;
        return 0;
    }

    cout << "syntax error..." << endl;
    return -1;
}