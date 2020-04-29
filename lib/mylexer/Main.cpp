#include "Tree.h"
#include "Utils.h"
using namespace std;

std::ostream& operator<<(std::ostream& os, Token al) {
	return os << static_cast<int>(al);
}

int main() {
	string message = "2^x";
	message = '(' + message + ')';

	Formula formula = tokenizer(message);
	int i = 0;
	for (Token token : formula.tokens) {
		if (token == Token::num) {
			i++;
		}else {
			cout << token << '\n';
		}
	}
	Tree tree(formula);
	for (int i = 0; i < 10; i++) {
		cout << "Number: " << tree.getOutput(i, 8) << endl;
	}

	return 0;
}
