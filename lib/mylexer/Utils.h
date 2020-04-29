#include <cctype>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
#pragma once

// Tokenizer, interpret characters into one of these operators
enum class Token : int {
	// Arithmetic operators
	add = 1, sub = 2, mult = 4, div = 3, pow = 10, log = 5, ln = 6, exp = 7,
	// Seperators
	lbrack = -99, rbrack = 99,
	// Number tmp
	num = 0,
	// Character
	x = -1, t = -2,
	// Special case
	empty = -5
};

std::ostream& operator << (std::ostream& os, const A& obj){
	os << static_cast<std::underlying_type<A>::type>(obj);
	return os;
}

// Tree-node sequence to structure
// the functions and number-sequence
struct TreeNode {
	Token token = Token::empty;
	TreeNode* parent = NULL;
	TreeNode* left = NULL;
	TreeNode* right = NULL;
};

struct Operand {
	enum { DOUBLE, CHAR } type;
	union {
		const char unknownValue;
		double value;
	};
};

struct Formula {
	vector<Token> tokens;
	vector<double> values;
};

Formula tokenizer(string const& input);
