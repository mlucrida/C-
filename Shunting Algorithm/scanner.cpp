#include <algorithm>

#include "scanner.h"

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
bool scan(TokenSequence& toks, const std::string& input)
{
	toks.clear();  //  Ensure token sequence is initially empty
	size_t pos = 0;
	while ( pos < input.length() )
	{
		//  Consume and ignore whitespace
		while ( input[pos] == ' ' || input[pos] == '\t' )
			pos++;
		//  Build number token, if applicable
		std::string num = "";
		while ( '0' <= input[pos] && input[pos] <= '9' )
			num += input[pos++];
		if ( num != "" )   //  Did we build a number token?
			toks.push_back(Token('$', atoi(num.c_str())));
		else if ( input[pos] == '*' || input[pos] == '+' 
			        || input[pos] == '(' || input[pos] == ')' )
			toks.push_back(Token(input[pos++], 0));  //  Add non-number token
		else  //  Illegal character in input string
			return false;
	}
	return true;
}


//  Convenient utility function to print a Token object
//  to an output stream like cout or an ofstream instance.
std::ostream& operator<<(std::ostream& out, const Token& tok)
{
	if ( tok.symbol == '$' )
		out << tok.value;
	else
		out << tok.symbol;
	return out;
}

//  Convenient utility function to print a Token sequence
//  to an output stream like cout or an ofstream instance.
std::ostream& operator<<(std::ostream& out, const TokenSequence& toks)
{
	out << '{';
	if ( toks.size() > 0 )
	{
		//  Print first element
		out << toks[0];
		//  Print rest of token sequence, if possible
		std::for_each(begin(toks) + 1,  end(toks), [&out](const Token& t) { out << ',' << t; });
	}
	out << '}';
	return out;
}
