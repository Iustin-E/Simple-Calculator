#include <iostream>
#include <string>
#include <stack>

using namespace std;

bool checkParantheses(string expression);

int main() {
	string expression;
	while (true) {
		cout << "Introdu o expresie: ";
		getline(cin, expression);
		cout << checkParantheses(expression) << endl;
	}
	/*while(!checkParantheses(expression)) {
		cout << "Paranteze gresite! Mai incearca: ";
		getline(cin, expression);
	}*/
		
}

bool isOpener(char a) {
	if (a == '(' || a == '[' || a == '{')
		return true;
	return false;
}

bool isCloser(char a) {
	if (a == ')' || a == ']' || a == '}')
		return true;
	return false;
}
bool isDigit(char a) {
	if (a >= '0' && a <= '9')
		return true;
	return false;
}
bool isChar(char a) {
	if (a >= 'a' && a <= 'z' ||
		a >= 'A' && a <= 'Z')
		return true;
	return false;
}
bool parMatch(char a, char b) {
	if (a == '(' && b == ')' ||
		a == '[' && b == ']' ||
		a == '{' && b == '}')
		return true;
	return false;
}

bool checkParantheses(string expression) {
	stack <char> S;
	for (int i = 0; i < expression.length(); i++) {
		if (expression[i] == ' ') continue;
		if (isOpener(expression[i]))
			S.push(expression[i]);
		else if (isCloser(expression[i])) {
			if (!S.empty() && parMatch(S.top(), expression[i]))
				S.pop();
			else
				return false;
		}
	}
	if (S.empty())
		return true;
	return false;
}