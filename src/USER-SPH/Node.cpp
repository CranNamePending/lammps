#include "Node.h"

Node::Node(Token token): m_token(token), m_left(nullptr), m_right(nullptr){
}

Node::Node(): m_token(Token::empty), m_left(nullptr), m_right(nullptr){
}
