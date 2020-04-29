#include "Tree.h"

#include <math.h> 

Tree::Tree(){
	m_topOperator = std::make_shared<OperatorNode>(Token::empty);
}

Tree::Tree(Formula const& formula){
	m_topOperator = std::make_shared<OperatorNode>(Token::empty);

	// Temporary storage of all operators/operands
	vector<Token> operators;
	stack<Operand> operands;
	Token previousOperator = Token::lbrack;

	// To index list of operands from Formula struct
	int i = 0;
	for (Token token : formula.tokens) {
		switch(token){
		case Token::num:{
			Operand operand = { Operand::DOUBLE, formula.values[i] };
			operand.value = formula.values[i];
			operands.push(operand);
			i++;
			break;
		}case Token::x:{
			Operand operand = { Operand::CHAR, 'x' };
			operands.push(operand);
			break;
		}case Token::t:{
			Operand operand = { Operand::CHAR, 't' };
			operands.push(operand);
			break;
		}default:
			if (token == Token::rbrack || (!operators.empty() && token < previousOperator)) {
				emptyStack(token == Token::rbrack, operators, operands);
				previousOperator = Token::lbrack;
			}
			if (token != Token::rbrack) {
				operators.push_back(token);
				previousOperator = token;
			}
		}
	}
}

void Tree::emptyStack(bool isRightBracket, vector<Token> &operators, stack<Operand> &operands){
	// At the end of ALL branches will be a number or x-t term,
	std::shared_ptr<Node> currentTop = getNextOperandNode(operands.top());
	operands.pop();

	Token nextToken = operators.back();
	while (!operators.empty()) {
		Token currentToken = nextToken;
		nextToken = operators.rbegin()[1];

		std::shared_ptr<Node> nextNode = std::make_shared<OperatorNode>(operators.back());
		operators.pop_back();
		nextNode->setRight(currentTop);
		currentTop = nextNode;

		// Either attach the currently-created tree to the end of this, or create the next operand node
		if (nextToken == Token::lbrack) {
			if (m_topOperator->getToken() == Token::empty) {
				std::shared_ptr<Node> node = getNextOperandNode(operands.top());
				operands.pop();
				currentTop->setLeft(node);
			} else {
				currentTop->setLeft(m_topOperator);
			}
			m_topOperator = currentTop;
			if (isRightBracket) {
				operators.pop_back();
			}
			break;
		} else {
			std::shared_ptr<Node> node = getNextOperandNode(operands.top());
			operands.pop();
			currentTop->setLeft(node);
		}
	}
}

std::shared_ptr<Node> Tree::getNextOperandNode(Operand operand) {
	if (operand.type == Operand::DOUBLE) {
		return std::make_shared<NumNode>(operand.value);
	} else {
		if (operand.unknownValue == 'x') {
			return std::make_shared<OperatorNode>(Token::x);
		} else if (operand.unknownValue == 't') {
			return std::make_shared<OperatorNode>(Token::t);
		} else {
			return std::make_shared<NumNode>(0);
		}
	}
}

double Tree::getOutput(double const& x, double const& t){
	return parseBranch(m_topOperator, x, t);
}

double Tree::parseBranch(std::shared_ptr<const Node> node, const double &x, const double &t) {
	switch (node->getToken()) {
	case Token::num:
		return (std::dynamic_pointer_cast<const NumNode>(node))->getValue();
	case Token::x:
		return x;
	case Token::t:
		return t;
	default:
		double right = parseBranch(node->getRight(), x, t);
		double left = parseBranch(node->getLeft(), x, t);
		switch (node->getToken()) {
		case Token::add:
			return left + right;
		case Token::sub:
			return left - right;
		case Token::mult:
			return left * right;
		case Token::div:
			return left / right;
		case Token::pow:
			return pow(left, right);
		}
	}
	return 0;
}
