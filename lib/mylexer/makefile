CXX = g++
CXXFLAGS = -lm -Wall -g -lstdc++ -std=c++11

a.out: Main.o Node.o OperatorNode.o NumNode.o Tree.o Utils.o
	$(CXX) $(CXXFLAGS) -o a.out Main.o Node.o OperatorNode.o NumNode.o Tree.o Utils.o

Main.o: Main.cpp Tree.h Utils.h
	$(CXX) $(CXXFLAGS) -c Main.cpp

Tree.o: Tree.h NumNode.h OperatorNode.h Utils.h

Node.o: Node.h Utils.h

OperatorNode.o: OperatorNode.h Node.h

NumNode.o: NumNode.h Node.h

Utils.o: Utils.h
