//  Name: Matt Lucrida
//  Assignment number: 5
//  Assignment: Arithmetic Expressions
//  File name: InfixToPostfix.cpp
//  Date last modified: February 17, 2014
//  Honor statement: I have neither given nor received any unauthorized help on this assignment. 

#include "InfixToPostfix.h"
#include "stack.h"

//  Uses a simplified form of Dijkstra's Shunting-yard algorithm to 
//  convert an infix token sequence (in) into a postfix token sequence (out).
//  See http://en.wikipedia.org/wiki/Shunting-yard_algorithm for
//  details.
//  The function's behavior is undefined if the in token sequence does not 
//  represent a valid infix arithmetic expression.
void infix_to_postfix(const TokenSequence& in, TokenSequence& out)
{
	out.clear();
	Stack<Token, 256> operators;	// full stack
	for (Token seq : in){			// while not at the end of TokenSequence in
		if (seq.symbol == '+'){		// if the token is a plus operator
			operators.push(seq);	// push element onto stack
		}
		else if (seq.symbol == '*'){	// if the token is a multiply operator
			operators.push(seq);		// push element onto stack
		}
		else if (seq.symbol == '('){	// if the token is '('
			operators.push(seq);		// push element onto stack
		}
		else if (seq.symbol == ')'){				// if the token is ')'
			while (operators.top().symbol != '('){	// until you find '('
				out.push_back(operators.top());		// push element onto queue
				operators.pop();					// pop element
			}
			operators.pop();						// pop off '('
		}
		else if (seq.symbol == '$'){	// if the token is a number
			out.push_back(seq);			// push element onto stack
		}
		else
			continue;
	}
	while (!operators.empty()){
		out.push_back(operators.top());
		operators.pop();
	}
}

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
int evaluate(const TokenSequence& toks)
{
	int num1 = NULL, num2 = NULL;	// initialize values to operate on
	int answer = NULL;				// initialize return value
	Stack<int, 256> numbers;		// initialize stack
	for (Token seq : toks){			// itterate through token sequence
		switch (seq.symbol){		// case statement for + or * or numbers
		case '+':					// addition case
				num1 = numbers.top();	// first number assigned value
				numbers.pop();			// pop off number from stack
				num2 = numbers.top();	// second number assigned value
				numbers.pop();			// pop off number from stack
				answer = num1 + num2;	// answer is calculated
				numbers.push(answer);	// and put back into the stack
				break;					
		case '*':						// multiplication case (same code logic as addition case)
				num1 = numbers.top();	
				numbers.pop();			
				num2 = numbers.top();	
				numbers.pop();			
				answer = num1 * num2;	// answer is calculated 
				numbers.push(answer);	
				break;					
		default:						// default case: numbers
				numbers.push(seq.value);// push number to the stack
				break;					
		}
	}
    return answer;  //  evaluate should never return a negative value
}


