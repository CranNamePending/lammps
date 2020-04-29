#include <stack>
#include <vector>

#include "NumNode.h"
#include "OperatorNode.h"
#include "Lexer.h"

#pragma once
class Tree {
public:
	Tree();
	Tree(Formula const& formula);
	double getOutput(const double& x, const double& t);
	void printTree() { printf("Node: %d\n", (int)m_topOperator->getToken()); }
private:
	std::shared_ptr<Node> m_topOperator;
	//std::vector<double> operands;
	std::shared_ptr<Node> getNextOperandNode(Operand operand);
	double parseValuesFromToken(const Token token, const double& left, const double& right);

	void emptyStack(bool isRightBracket, vector<Token>& operators, stack<Operand>& operands);
	double parseBranch(std::shared_ptr<const Node> node, double const& x, double const& t);
};
