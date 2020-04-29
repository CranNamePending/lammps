#include "Lexer.h"

Token parseCharacter(char x);

Formula tokenizer(string const& input){
	vector<Token> tokens;
	vector<double> values;
	string nextValue;
	string multiChar;
	multiChar.clear();

	for (const char& c : input) {
		// Parse double values, to ensure a whole number is collected
		if ((c <= (int)57 && c >= 48) || c == 46) {
			nextValue.push_back(c);
			continue;
		}else if (c == 32) {
			continue;
		}	else if ((c == 108 || c == 76) && multiChar.empty()) {
			multiChar.push_back('l');
			continue;
		// ln
		}else if ((c == 78 || c == 110) && multiChar.size() == 1) {
			multiChar.clear();
			tokens.push_back(Token::ln);
			continue;
		}else if ((c == 79 || c == 111) && multiChar.size() == 1) {
			multiChar.push_back('o');
			continue;
		// Log
		}
		else if ((c == 71 || c == 103) && multiChar.size() == 2) {
			multiChar.clear();
			tokens.push_back(Token::log);
			continue;
		}else if(c == '-'){
			if (nextValue.empty() || tokens.back() == Token::rbrack) {
				nextValue.push_back('-');
			}else {
				tokens.push_back(Token::num);
				double value = atof(nextValue.c_str());
				nextValue.clear();
				values.push_back(value);
				tokens.push_back(parseCharacter(c));
			}
		}else {
			// Store number, with Token informing interpretter to 
			// grab values from Value system.
			if (!nextValue.empty()) {
				tokens.push_back(Token::num);
				double value = atof(nextValue.c_str());
				nextValue.clear();
				values.push_back(value);
			}
			tokens.push_back(parseCharacter(c));
		}
	}
	if (!nextValue.empty()) {
		tokens.push_back(Token::num);
		double value = atof(nextValue.c_str());
		values.push_back(value);
	}

	Formula form;
	form.tokens = tokens;
	form.values = values;
	return form;
}

// Character -> Token interpretter.
Token parseCharacter(char x) {
	switch (x) {
	case '+':
		return Token::add;
	case '-':
		return Token::sub;
	case '*':
		return Token::mult;
	case '/':
		return Token::div;
	case '^':
		return Token::pow;
	case '(':
		return Token::lbrack;
	case ')':
		return Token::rbrack;
	case 'E':
	case 'e':
		return Token::exp;
	case 'X':
	case 'x':
		return Token::x;
	case 'T':
	case 't':
		return Token::t;
	default:
		printf("\aUnknown Token!\n");
		exit(1);
	}
}


