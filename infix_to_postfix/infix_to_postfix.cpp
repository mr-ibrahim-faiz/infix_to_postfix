#include "infix_to_postfix.h"

#include<algorithm>
using std::remove_if;

#include<stdexcept>
using std::runtime_error;

#include<stack>
using std::stack;

// checks assertion c >=-1 && c <=255
int passes_assertion(int c)
// checks if the assertion c >=-1 && c <=255 is true for a specified character
// returns 1 (true) if it is the case
// returns 0 (false) otherwise
{
	if (c >= -1 && c <= 255)
		return 1;
	else
		return 0;
}

// checks assertion c >=-1 && c <=255 for each character of a string expression
int passes_assertion(const string& expression)
// checks if the assertion c >=-1 && c <=255 is true each character of a string expression
// returns 1 (true) if it is the case
// returns 0 (false) otherwise
{
	for (char c : expression)
		if (!passes_assertion(c))
			return 0;
	return 1;
}

// clears expression
void clear_expression(string& expression) noexcept
// clears expression passed as argument by removing whitespaces, changing 'x' to '*' and ':' unto '/'
{
	// remove whitespaces from expression
	// checks assertion c >=-1 && c <=255 before using isspace
	if (passes_assertion(expression))
		expression.erase(remove_if(expression.begin(), expression.end(), isspace), expression.end());
	else
		expression = "";

	// replace ':', 'x' by '/' and '*'
	for (size_t i = 0; i < expression.size(); ++i) {
		switch (expression[i]) {
		case 'x':
			expression[i] = '*';
			break;
		case ':':
			expression[i] = '/';
			break;
		default:
			break;
		}
	}
}

// checks parentheses
bool check_parentheses(const string& expression) noexcept
// returns true if nothing is wrong with the parentheses
// i.e odd number of parentheses, unclosed parentheses
{
	// validation variable
	// it must never be less than 0
	int validation{ 0 };
	for (size_t i = 0; i < expression.size(); ++i) {
		if (expression[i] == '(')
			++validation;
		else if (expression[i] == ')')
			--validation;
		else {}

		// validation
		if (validation < 0)
			return false;
	}

	// validation
	if (validation == 0)
		return true;

	return false;
}

// checks if a char is a representation of a digit
bool is_a_digit(const char& c) noexcept
// checks if the argument is the representation of a digit [0, 10)
// returns true if the argument is the representation of a digit
{
	switch (c)
	{
	case '0': case '1': case '2': case '3': case '4': case '5':
	case '6': case '7': case '8': case '9':
		return true;
	default:
		return false;
	}
}

// checks if an expression is valid
bool is_valid(const string& expression) noexcept
// checks if an expression is valid by using a set of rules
// i.e. number of parentheses, invalid characters, etc
// returns true if everything is fine according to these rules
{
	// length of the expression
	size_t length = expression.size();

	// returns false if there's something wrong with the parentheses
	if (!check_parentheses(expression))
		return false;

	// returns false if the first character cannot be represented as a digit,
	// exceptions: the first character can be '+', '-', '.' or '('
	switch (expression[0])
	{
	case '+': case '-': case '(': case '.':
		break;
	default:
		if (!is_a_digit(expression[0]))
			return false;
		break;
	}

	// returns false if the last character cannot be represented as a digit
	// exceptions: the last character can be ')' or '.'
	if (!is_a_digit(expression[length - 1])) {
		switch (expression[length - 1]) {
		case ')': case '.':
			break;
		default:
			return false;
		}
	}

	// returns false if two caracters are following each other
	for (size_t i = 0; i < length - 1; ++i) {
		// if the current character can be represented as a digit, it is ignored
		if (is_a_digit(expression[i]))
			continue;

		// if an invalid float (such as .1.2.) is detected, it returns false
		if (expression[i] == '.') {
			size_t j = i + 1;
			while (expression[j++]) {
				// if the current character can be represented as a digit, it is ignored
				if (is_a_digit(expression[j - 1]))
					continue;
				// returns false if a second '.' is found in an operand
				else if (expression[j - 1] == '.')
					return false;
				else
					break;
			}
		}

		// returns false if two caracters which are not allowed to follow each other follow each others
		switch (expression[i]) {
		case '*': case '/': case '+': case '-': case 'e': case '^':
			// accepts *(, /(, +(, -(, *., /., +., -., ^(, ^., e(, e.
			// refuses for example *) or *L
			if (expression[i + 1] == '(');
			else if (expression[i + 1] == '.');
			else if ((expression[i + 1] == '+' || expression[i + 1] == '-') && expression[i] == 'e');
			else if ((expression[i + 1] == '+' || expression[i + 1] == '-') && expression[i] == '^');
			else if ((expression[i + 1] == '+' || expression[i + 1] == '-') && expression[i] == '*');
			else if ((expression[i + 1] == '+' || expression[i + 1] == '-') && expression[i] == '/');
			else
				if (!is_a_digit(expression[i + 1]))
					return false;
		case '(':
			// accepts (+, (-, ((, (.
			// refuses for example (* or (L
			switch (expression[i + 1]) {
			case '+': case '-': case '(': case '.':
				break;
			default:
				if (!is_a_digit(expression[i + 1]))
					return false;
			}
			break;

		case ')': case '.':
			// accepts )+, )-, )*, )/, )), .+, .-, .*, ./, .), )^, .^, )e, .e
			// refuses for example )( or .L
			switch (expression[i + 1]) {
			case '+': case '-': case '*': case '/': case '^': case ')': case 'e':
				break;
			default:
				if (!is_a_digit(expression[i + 1]))
					return false;
			}
			break;

		default:
			// if the current character is not a valid character, returns false
			return false;
			break;
		}
	}

	return true;
}

// checks if a char is a valid unary operator + or -
bool is_unary_plus_or_minus(const char& c) noexcept
// checks if the argument is the representation of a valid unary operator +, or -
// returns true if it is the case
{
	switch (c)
	{
	case '+': case '-':
		return true;
	default:
		return false;
	}
}

// checks if a character is allowed in a number
bool is_allowed_in_number(const char& c) noexcept
// checks if the character passed as argument is allowed in a number
// returns true if it is the case
{
	if (is_a_digit(c) || is_unary_plus_or_minus(c) || c == '.' || c == 'e')
		return true;
	return false;
}

// checks if a char is a valid operator
bool is_an_operator(const char& c) noexcept
// checks if the argument is the representation of a valid operator +, -, * / or ^
// returns true if it is the case
{
	switch (c)
	{
	case '+': case '-': case '*': case '/': case '^':
		return true;
	default:
		return false;
	}
}

// converts infix expressions to postfix expression
string infix_to_postfix(const string& infix)
// uses the Shunting-yard algorithm to convert an infix expression to postfix expression
// the infix expression must be a valid infix expression
// returns the postfix expression
{
	string output = "";
	stack<char> operators;

	if (!is_valid(infix))
		throw runtime_error("invalid infix expression.");

	for (size_t i = 0; i < infix.size(); ++i) {

		if (is_allowed_in_number(infix[i])) {
			switch (infix[i]) {
			case '+': case '-':
				if (i == 0 || infix[i - 1] == 'e' || infix[i - 1] == '(')
					output.push_back(infix[i]);
				else {
					if (operators.empty() || operators.top() == '(') {
						output.push_back(' ');
						operators.push(infix[i]);
					}
					else {
						while (!operators.empty() && operators.top() != '(') {
							output.push_back(' ');
							output.push_back(operators.top());
							operators.pop();
						}
						output.push_back(' ');
						operators.push(infix[i]);
					}
				}
				break;

			default:
				output.push_back(infix[i]);
				break;
			}
		}
		else if (is_an_operator(infix[i])) {
			switch (infix[i]) {
			case '/': case '*':
				if (operators.empty() || operators.top() == '+' || operators.top() == '-' || operators.top() == '(') {
					output.push_back(' ');
					operators.push(infix[i]);
				}
				else {
					while (!(operators.empty() || operators.top() == '+' || operators.top() == '-' || operators.top() == '(')) {
						output.push_back(' ');
						output.push_back(operators.top());
						operators.pop();
					}
					output.push_back(' ');
					operators.push(infix[i]);
				}
				break;

			case '^':
					output.push_back(' ');
					operators.push(infix[i]);
				break;

			default:
				break;
			}
		}
		else {
			switch (infix[i]) {
			case '(':
				operators.push(infix[i]);
				break;
			case ')':
				while (operators.top() != '(') {
					output.push_back(' ');
					output.push_back(operators.top());
					operators.pop();
				}
				operators.pop();
				break;
			default:
				break;
			}
		}
	}

	while (!operators.empty()) {
		output.push_back(' ');
		output.push_back(operators.top());
		operators.pop();
	}

	return output;
}