#pragma once

#include "Node.h"

class NumNode: public Node {
public:
	NumNode(const double& value):
		Node(Token::num), m_value(value) {}

	const double getValue() const { return m_value; }

private:
	double m_value;
};

