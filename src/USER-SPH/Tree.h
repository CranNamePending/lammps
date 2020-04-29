#include <stack>
#include <vector>

#include "NumNode.h"
#include "OperatorNode.h"
#include "Lexer.h"

#pragma once
class Tree
{
public:
	Tree();
	Tree(Formula const& formula);
	double getOutput(const double& x, const double& t);

private:
	std::shared_ptr<Node> m_topOperator;
	//std::vector<double> operands;
	std::shared_ptr<Node> getNextOperandNode(Operand operand);

	bool simplifyRecursive(std::shared_ptr<const Node> node, double& value);
	void simplify();

	void emptyStack(bool isRightBracket, vector<Token> &operators, stack<Operand> &operands);
	double parseBranch(std::shared_ptr<const Node> node, double const& x, double const& t);
};
