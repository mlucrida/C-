//  Name: Matt Lucrida
//  Assignment number: 5
//  Assignment: Arithmetic Expressions
//  File name: stack.h
//  Date last modified: February 17, 2014
//  Honor statement: I have neither given nor received any unauthorized help on this assignment. 

#ifndef _DEFINED_STACK_H_
#define _DEFINED_STACK_H_

#include <iostream>
//  Represents a generic stack abstract data type
//  A stack can hold up to N objects of type T
template <typename T, int N>
class Stack{
private:
	T stack[N];		// create stack with given size N
	int itterator;	// create an itterator
	int cap;		// capacity variable

public:
	Stack(){
		itterator = -1;	// initialize itterator at -1
		cap = (N - 1);	// initialize capacity at N-1
	};

	/*push function: adds an element to the top of the stack*/
	void push(T element){
		if (!full()){														// only push elements if stack has room
			itterator++;													// move to available position
			stack[itterator] = element;										// insert element to stack
		}
		//else
			//std::cout << "FULL STACK: UNABLE TO PUSH ELEMENT ONTO STACK.\n";		// stack has no room

	};

	/*pop function: removes the top element from the stack*/
	void pop(){
		if (!empty())										// only pop elements if the stack contains some
			itterator--;									// decrement itterator (popping)
		//else
			//std::cout << "EMPTY STACK: NO ELEMENTS TO POP.\n";	// stack is empty
	};

	/*top function: read the top element from the stack*/
	T top(){
		if (!empty())										// only read elements if the stack contains some
			return stack[itterator];						// read the element
		else{
			//std::cout << "EMPTY STACK: NO ELEMENTS TO READ.\n";	// stack is empty
			return stack[0];
		}
	};

	/*full function: returns true if the stack is full*/
	bool full(){
		if (itterator == cap)	// if the itterator is indexing the last space in the array (cap == N-1)
			return true;		// the stack is full
		else
			return false;		// the stack isn't full
	};

	/*empty function: returns ture if teh stack is empty*/
	bool empty(){
		if (itterator == -1)	// if the itterator is indexing out of scope
			return true;		// the stack is empty
		else
			return false;		// the stack isn't empty
	};
};

#endif
