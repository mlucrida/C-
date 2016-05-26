#ifndef _DEFINED_SCANNER_H_
#define _DEFINED_SCANNER_H_

#include <ostream>
#include <vector>
#include <string>

//  Character tokens are one of '(', ')', '+', '*'
//  Numeric tokens are integers (their symbol is '$')
struct Token
{
	char symbol;
	int value;

	Token(char symbol, int value): symbol(symbol), value(value) {}
	Token(): symbol('$'), value(0) {}
};

//  A sequence of tokens implemented as a vector of Token objects
typedef std::vector<Token> TokenSequence;

//  Accepts a token sequence (toks) and an input string (input).
//  input should be a string representing an infix arithmetic 
//  expression involving only non-negative integers, addition, 
//  subtraction, and parentheses.
//  The function converts the input string into a sequence of 
//  tokens in toks.  This allows multi-character integers 
//  (like 312) to be treated as a single token rather than three
//  separate characters.  The function strips out any whitespace 
//  characters (spaces and tabs) along the way.
//  The function returns true if it can successfully tokenize the
//  string.  It returns false if it encounters characters other
//  digits, parentheses, addition, multiplication, and whitespace.
//
//  The function's behavior is undefined if input does not 
//  represent a valid infix arithmetic expression.
bool scan(TokenSequence& toks, const std::string& input);

//  Convenient utility function to print a Token object
//  to an output stream like cout or an ofstream instance.
std::ostream& operator<<(std::ostream& out, const Token& tok);

//  Convenient utility function to print a Token sequence
//  to an output stream like cout or an ofstream instance.
std::ostream& operator<<(std::ostream& out, const TokenSequence& toks);

#endif
