This is a simple example of structuring a parser using cpp-peglib.

I had to do something remarkably ugly in the AST tree generation and
introduce a ParseTreeNode class, simply because I couldn't get
peglib to accept an abstract base class. If someone knows a way around this,
please let me know.

On OS X, I built this with

     clang -g -I .. -std=c++11 -l c++ -o parser *.cc

I believe something similar works for g++.


Dave
