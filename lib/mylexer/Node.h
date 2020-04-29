#pragma once
#include <memory>

#include "Utils.h"

class Node
{
protected:
	std::shared_ptr<const Node> m_left, m_right;
	Token m_token;

public:
	Node(Token token);
	Node();
	virtual ~Node(){}

	void setLeft(std::shared_ptr<const Node> node) { m_left = node; }
	void setRight(std::shared_ptr<const Node> node) { m_right = node; }

	Token getToken() const { return m_token; }
	std::shared_ptr<const Node> getLeft() const { return m_left; }
	std::shared_ptr<const Node> getRight() const { return m_right; }
};

