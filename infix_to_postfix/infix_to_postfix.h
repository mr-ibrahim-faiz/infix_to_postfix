#pragma once

#include<string>
using std::string;

// checks assertion c >=-1 && c <=255
int passes_assertion(int);

// checks assertion c >=-1 && c <=255 for each character of a string expression
int passes_assertion(const string&);

// clears expression
void clear_expression(string&) noexcept;

// checks parentheses
bool check_parentheses(const string&) noexcept;

// checks if a char is a representation of a digit
bool is_a_digit(const char&) noexcept;

// checks if an expression is valid
bool is_valid(const string&) noexcept;

// checks if a char is a valid unary operator + or -
bool is_unary_plus_or_minus(const char&) noexcept;

// checks if a character is allowed in a number
bool is_allowed_in_number(const char&) noexcept;

// checks if a char is a valid operator
bool is_an_operator(const char&) noexcept;

// converts infix expressions to postfix expression
string infix_to_postfix(const string&);