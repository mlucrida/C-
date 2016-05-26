#include <iostream>
#include "InfixToPostfix.h"

using namespace std;

//  Allows the user to enter infix strings and attempts to 
//  convert them to postfix form and evaluates them. 
int main()
{
	char buffer[256];          //  Buffer for user input
	string infix;              //  User's input string object
	TokenSequence postfix;     //  Postfix token sequence
	cout << "Press enter (empty expression) to exit" << endl;
	for ( ;; )
	{
		cin.getline(buffer, 255);
		infix = buffer;            //  Convert to a string object
		if ( infix == "" )
			break;   //  Empty input quits the program
		TokenSequence tokens;
		if ( scan(tokens, infix) )
		{
			cout << tokens << endl;  //  Print original infix token sequence
			infix_to_postfix(tokens, postfix);
			cout << postfix << endl; //  Print postfix token sequence
			cout << "Value = " << evaluate(postfix) << endl;
		}
		else
			cout << "Illegal expression" << endl;
	} 
}
