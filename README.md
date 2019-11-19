This is a simple example of structuring a parser using cpp-peglib.

I had to do something remarkably ugly in the AST tree generation and
introduce a ParseTreeNode class, simply because I couldn't get
peglib to accept an abstract base class. If someone knows a way around this,
please let me know.

On OS X, I built this with

     clang -g -I «location of cpp-peglib» -std=c++11 -l c++ -o parser *.cc

For g++, I use

     g++ -I «location of cpp-peglib» -o parser *.cc

Tested on OS X 9Apple LLVM version 10.0.1 (clang-1001.0.46.4)
and Ubuntu (g++ (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0)


Dave
