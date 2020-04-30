#include "Tree.h"

#include <math.h> 

Tree::Tree(): m_topOperator(std::make_shared<OperatorNode>(Token::empty)) {}

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
			printf("Num\n");
			Operand operand = { Operand::DOUBLE};
			operand.value = formula.values[i];
			operands.push(operand);
			i++;
			break;
		}case Token::x:{
		}case Token::t:{
			printf("x or t\n");
			Operand operand = { Operand::ENUM, token };
			operands.push(operand);
			break;
		}default:
			printf("other value\n");
			if (token == Token::rbrack || (!operators.empty() && token < previousOperator)) {
				printf("Parsing\n");
				emptyStack(token == Token::rbrack, operators, operands);
				previousOperator = Token::lbrack;
			}
			if (token != Token::rbrack) {
				operators.push_back(token);
				previousOperator = token;
			} else if (operators.size() > 1) {
				previousOperator = *(operators.rbegin()+1);
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

			// insert new tree into system
			// Special case full brackets, or m_top 
			// Simplification system
			if (m_topOperator->getToken() == Token::empty) {
				if (operands.top().type == Operand::DOUBLE && currentTop->getRight()->getToken() == Token::num) {
					double value = parseValuesFromToken(currentTop->getToken(), operands.top().value, (std::dynamic_pointer_cast<const NumNode>(currentTop->getRight()))->getValue());
					currentTop = make_shared<NumNode>(value);
				} else {
					std::shared_ptr<Node> node = getNextOperandNode(operands.top());
					currentTop->setLeft(node);
				}
				operands.pop();
			} else {
				// Simplify, either set m_topOperator left of currentTop operator, or replace with the calculation of all
				if (m_topOperator->getToken() == Token::num && currentTop->getRight()->getToken() == Token::num) {
					double value = parseValuesFromToken(currentTop->getToken(),	// current operator tag
						(std::dynamic_pointer_cast<const NumNode>(m_topOperator))->getValue(), // Left, current Top node
						(std::dynamic_pointer_cast<const NumNode>(currentTop->getRight()))->getValue()); // right, next operand
					currentTop = make_shared<NumNode>(value);
				} else {
					currentTop->setLeft(m_topOperator);
				}
			}
			m_topOperator = currentTop;
			if (isRightBracket) {
				operators.pop_back();
			}
			break;
		} else {
			// Simplification system
			if (operands.top().type == Operand::DOUBLE && currentTop->getRight()->getToken() == Token::num) {
				double value = parseValuesFromToken(currentTop->getToken(), operands.top().value, (std::dynamic_pointer_cast<const NumNode>(currentTop->getRight()))->getValue());
				currentTop = make_shared<NumNode>(value);
			} else {
				std::shared_ptr<Node> node = getNextOperandNode(operands.top());
				currentTop->setLeft(node);
			}
			operands.pop();
		}
	}
}

double Tree::parseValuesFromToken(const Token token, const double &left, const double &right) {
	switch (token) {
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
	default:
		return 0;
	}
}

std::shared_ptr<Node> Tree::getNextOperandNode(Operand operand) {
	if (operand.type == Operand::DOUBLE) {
		return std::make_shared<NumNode>(operand.value);
	} else {
		if (operand.unknownValue == Token::x || operand.unknownValue == Token::t) {
			return std::make_shared<OperatorNode>(operand.unknownValue);
		} else {
			return std::make_shared<NumNode>(0);
		}
	}
}

double Tree::getOutput(double const& x, double const& t){
	return exp(parseBranch(m_topOperator, x, t));
}

double Tree::parseBranch(std::shared_ptr<const Node> node, const double &x, const double &t) {
	switch (node->getToken()) {	
	case Token::num:
		return (std::dynamic_pointer_cast<const NumNode>(node))->getValue();
	case Token::x:
		return x;
	case Token::t:
		return t;
	case Token::empty:
		return 0;
	default:
		double right = parseBranch(node->getRight(), x, t);
		double left = parseBranch(node->getLeft(), x, t);
		return parseValuesFromToken(node->getToken(), left, right);
	}
	return 0;
}
