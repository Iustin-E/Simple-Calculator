#include <iostream>
#include <string>
#include <stack>

using namespace std;

bool checkParantheses(string expression);

int SolvePostfix(string expression);

string postfixConvertor(string expression);				// DOAR PT TEST - A SE STERGE

int main() {
	string expression;
	cout << "Introdu o expresie: ";
	getline(cin, expression);
	while(!checkParantheses(expression)) {
		cout << "Paranteze gresite! Mai incearca: ";
		getline(cin, expression);
	}
	string postfix = postfixConvertor(expression);
	cout << "Postfix: " << postfix << endl;
	int result = SolvePostfix(expression);
	cout << result;
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

bool parMatch(char a, char b) {
	if (a == '(' && b == ')' ||
		a == '[' && b == ']' ||
		a == '{' && b == '}')
		return true;
	return false;
}
bool isOperator(char a) {
	if (a == '+' || a == '-' || a == '*' || a == '/' || a == '^')
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

short getWeight(char a) {
	short weight = -1;
	switch (a) {
	case '+':
	case '-':
		weight = 1;
		break;
	case '*':
	case '/':
		weight = 2;
		break;
	case '^':
		weight = 3;
		break;
	}
	return weight;
}

bool isHigher(char a, char b) {
	short w1 = getWeight(a);
	short w2 = getWeight(b);
	if (w1 == w2) {
		if (a == '^' && b == '^')
			return false;
		return true;

	}
	return w1 > w2 ? true : false;
}

bool isOperand(char a) {
	if (a >= 'a' && a <= 'z' ||
		a >= 'A' && a <= 'Z' ||
		a >= '0' && a <= '9')
		return true;
	return false;
}

string postfixConvertor(string expression) {
	string postfix = "";
	stack <char> S;
	for (int i = 0; i < expression.length(); i++) {
		if (expression[i] == ' ') continue;
		if (isOperand(expression[i])) 	// daca este cifra/litera			
			postfix += expression[i];	// nu merge cu mai multe cifre si sa formez un numar. imi retunreaza un cod ascii
										// care este convertit in litera
								
		// PARANTEZE
		else if (isOpener(expression[i]))		// daca este paranteza deschisa
			S.push(expression[i]);
		else if (isCloser(expression[i])) {		// daca este paranteza inchisa
			while (S.top() != '(') {
				postfix += S.top();
				S.pop();
			}
			S.pop();
		}

		else if (isOperator(expression[i])) {
			while (	!S.empty()&& isHigher(S.top(), expression[i]) && S.top() != '(') {
				postfix += S.top();			// cand vine un element cu prioritate mai mica, trecem tot ce avem in stack
				S.pop();
			}
			S.push(expression[i]);
		}
	}
	while (!S.empty()) {	// cand teminam expressia trecem tot ce a ramas in stack
		postfix += S.top();
		S.pop();
	}
	return postfix;
}

