//  File:   InfixToPostfix.h
//  Author: Rick Halterman
//  Date:   1/27/2013 9:24:19 PM

#ifndef _DEFINED_INFIXTOPOSTFIX_H_
#define _DEFINED_INFIXTOPOSTFIX_H_

#include "scanner.h"


//  Uses a simplified form of Dijkstra's Shunting-yard algorithm to 
//  convert an infix token sequence (in) into a postfix token sequence (out).
//  See http://en.wikipedia.org/wiki/Shunting-yard_algorithm for
//  details.
//  The function's behavior is undefined if the in token sequence does not 
//  represent a valid infix arithmetic expression.
void infix_to_postfix(const TokenSequence& in, TokenSequence& out);


//  Accepts a token sequence in postfix (RPN)
//  form.  Returns the value of the postfix
//  expression represented by the token sequence.
//  Uses a stack of integers to assist in the
//  evaluation process:
//  See a number?  Push it onto the stack.
//  See an operator?  Pop the top two elements
//  off the stack, apply the operator, and push
//  the result back onto the stack.
//  No more tokens left in the postfix token
//  sequence?  Return the value on the top of the
//  stack.
//  The function's behavior is undefined if the
//  toks token sequence does not represent a 
//  valid infix arithmetic expression.
int evaluate(const TokenSequence& toks);

#endif

