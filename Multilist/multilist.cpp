//  Name: Matt Lucrida
//  Assignment number: 4
//  Assignment: multilist
//  File name: multilist.cpp
//  Date last modified: February 10, 2014
//  Honor statement: I have neither given nor received any unauthorized help on this assignment. 

#include <iostream>
#include <algorithm>
#include "multilist.h"
using namespace std;

/////////////////////////////////// 
// creates a new empty multilist //
///////////////////////////////////
Multilist::Node::Node(int id, std::string name, int age){
	Node::id = id; Node::name = name; Node::age = age;		// match appropriate variables
};

///////////////////////////////////////////////////////
//	Multilist contructor, initializes first and last //
//	and connects them to each other					 //
///////////////////////////////////////////////////////
Multilist::Multilist(){
	//assigns first and last unique values
	first = new Node(-1, "", -1);
	last = new Node(-1, "", -1);

	// connects all first_next pointers to last
	first->next_id = last;
	first->next_age = last;
	first->next_name = last;

	// connects all last_prev pointers to first
	last->prev_id = first;
	last->prev_age = first;
	last->prev_name = first;
};
////////////////////////////////////////////////////////
// Properly deallocates tehs pace held by a multilist //
////////////////////////////////////////////////////////
Multilist::~Multilist(){
	Node *it = first;				// initialize a node pointer to point to the node that will be deleted
	Node *next = first->next_id;	// initializes a node pointer to point the the next node in line

	while (it != last){			// goes through the list deleting all nodes from first up to BEFORE last
		delete it;				// Node is deleted
		it = next;				// next node to be deleted is pointed to
		next = next->next_id;	// temporary node is shifted to the next node
	}
	delete it;					// last node is deleted

};
////////////////////////////////////////////////////////////////
// Adds a new person to the list with the given last name,	  //
// ID number, and age.  Duplicate IDs are not allowed.		  //
// Return true if the other person was successfully inserted; //
// otherwise, returns false									  //
////////////////////////////////////////////////////////////////
bool Multilist::insert(int id, std::string name, int age){
	transform(begin(name), end(name), begin(name), ::toupper);	// converts name to all uppercase letters
	Node *new_node = new Node(id, name, age);		// a new node is created.
	Node *check = first;							// Node pointer check is initialized and assigned to first
													
	while (check != last && check->id < id			// Loops through the list until the appropriate spot to insert the new node is found
		    && check->id != id)						// SPECIAL ID CONDITION: NO DUPLICATE IDS
		check = check->next_id;						// goes to the next node
	if (check->id == id)							// duplicate ID is found
		return false;								// return false
	else{											// valid ID entry
		new_node->next_id = check;						// link to the next node in the list
		new_node->prev_id = check->prev_id;				// link to the previous node in the list
		check->prev_id->next_id = new_node;				// relink the previous node's "next" to the new node
		check->prev_id = new_node;						// relink the next node's "previous" to the new node
	}
////////////////////////////////////////////////////////
// the same coding logic is repeated for age and name //
// without the duplicate ID special case			  //
////////////////////////////////////////////////////////
	check = first;
	while (check != last && check->age < age)
		check = check->next_age;
	new_node->next_age = check;
	new_node->prev_age = check->prev_age;
	check->prev_age->next_age = new_node;
	check->prev_age = new_node;


	check = first;
	while (check != last && check->name < name)
		check = check->next_name;					
	new_node->next_name = check;					
	new_node->prev_name = check->prev_name;			
	check->prev_name->next_name = new_node;			
	check->prev_name = new_node;					

	return true;
};
/////////////////////////////////////////////////////////////////////
// Removes the person with the given ID number.					   //
// Returns true if the person was removed; otherwise, return false //
/////////////////////////////////////////////////////////////////////
bool Multilist::remove(int id){
	Node *remove = first;							// Begin at First Node
	while (remove->id != id && remove != last)		// itterate through until the end of the list
		remove = remove->next_id;					// next node
	if (remove == last)								// if node with id isn't found . . .
		return false;
	else{											// node with id IS found. . .
		// relink ID pointers	
		remove->prev_id->next_id = remove->next_id;
		remove->next_id->prev_id = remove->prev_id;
		// relink Name pointers
		remove->prev_name->next_name = remove->next_name;
		remove->next_name->prev_name = remove->prev_name;
		// relink Age pointers
		remove->prev_age->next_age = remove->next_age;
		remove->next_age->prev_age = remove->prev_age;

		delete remove;								// delete the node after all things are relinked
		return true;								// completed
	}
	
};
////////////////////////////////////////////////////////////////////////////
// ALL PRINTING LOGIC FOLLOWS THE TEMPLATE:								  //
// define the start point (Node *current = first->next_X or last->prev_X) //
// print until the end point is reached (current != first or last)		  //
// print order: name, age, ID											  //
// move to next node (current = current->next_X or current->prev_X)		  //
////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////
// Print the contents in order by ID number //
//////////////////////////////////////////////
void Multilist::print_by_ID(){
	Node *current = first->next_id;		// start point
	while (current != last){			// end point
		cout << "(" << 
			current->name << ", " << 
			current->age << ", " << 
			current->id << ")\n";
		current = current->next_id;		// continue through list
	}
};
//////////////////////////////////////////////////////
// Print the contents in reverse order by ID number //
//////////////////////////////////////////////////////
void Multilist::print_by_ID_reverse(){
	Node *current = last->prev_id;		// start point
	while (current != first){			// end point
		cout << "(" <<
			current->name << ", " <<
			current->age << ", " <<
			current->id << ")\n";
		current = current->prev_id;		// continue through list
	}
};
//////////////////////////////////////////////
// Print the contents in order by last name //
//////////////////////////////////////////////
void Multilist::print_by_name(){
	Node *current = first->next_name;		// start point
	while (current != last){				// end point
		cout << "(" <<
			current->name << ", " <<
			current->age << ", " <<
			current->id << ")\n";
		current = current->next_name;		// continue through list
	}
};
//////////////////////////////////////////////////////
// Print the contents in reverse order by last name //
//////////////////////////////////////////////////////
void Multilist::print_by_name_reverse(){
	Node *current = last->prev_name;		// start point
	while (current != first){				// end point
		cout << "(" <<
			current->name << ", " <<
			current->age << ", " <<
			current->id << ")\n";
		current = current->prev_name;		// continue through list
	}
};
/////////////////////////////////////////////////////////
// Print the contents in order from oldest to youngest //
/////////////////////////////////////////////////////////
void Multilist::print_by_age(){
	Node *current = first->next_age;		// start point
	while (current != last){				// end point
		cout << "(" <<
			current->name << ", " <<
			current->age << ", " <<
			current->id << ")\n";
		current = current->next_age;		// continue through list
	}
};
/////////////////////////////////////////////////////////
// Print the contents in order from youngest to oldest //
/////////////////////////////////////////////////////////
void Multilist::print_by_age_reverse(){
	Node *current = last->prev_age;		// start point
	while (current != first){			// end point
		cout << "(" <<
			current->name << ", " <<
			current->age << ", " <<
			current->id << ")\n";
		current = current->prev_age;	// continue through list
	}
};
