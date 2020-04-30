#include <cctype>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
#pragma once

// Tokenizer, interpret characters into one of these operators
enum class Token : int {
	// Arithmetic operators
	add = 1, sub = 2, mult = 4, div = 3, pow = 10, 
	// Do Not Work! Do not use!
	log = 5, ln = 6, exp = 7,
	// Seperators
	lbrack = -99, rbrack = 99,
	// Number tmp
	num = 0,
	// Character
	x = -1, t = -2,
	// Special case
	empty = -5
};

struct Operand {
	enum { DOUBLE, ENUM } type;
	union {
		Token unknownValue;
		double value;
	};
};

struct Formula {
	vector<Token> tokens;
	vector<double> values;
};

Formula tokenizer(string const& input);
