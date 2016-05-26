//  Name: Matt Lucrida
//  Assignment number: 9
//  Assignment: Hash Table with Closed Hashing
//  File name: hashtable.cpp
//  Date last modified: March 27, 2014
//  Honor statement: I have neither given nor received any unauthorized help on this assignment. 

#include <iostream>
#include <algorithm>
#include "hashtable.h"
using namespace std;

/*
CONSTRUCTER ~ initialize functions, and table vector
*/
HashTable::HashTable(unsigned table_size, int(*h)(const string&), int(*f)(int)) : hash(h), f(f){
	table = vector<Record *>(table_size, nullptr);
};

/*
DESTRUCTOR ~ delete all contents
*/
HashTable::~HashTable(){
	int size = table.size();
	for (int i = 0; i < size; i++)
		delete table[i];
};

/*
LOCATE FUNCTION
*/
int HashTable::locate(const string& s) const{
	int size = table.size();				// initialize size variable
	int index = hash(s);					// set index to hash
	for (int i = 0; i < size; i++){			// iterate through table
		int probe = ((index + f(i)) % size);// probe for a location
		if (table[probe] == nullptr ||		// if empty location or
			table[probe]->key == s)			// if keys match
			return probe;					// return its index
	}

	return -1;								// no locations found
};

/*
LOCATE FUNCTION
*/
bool HashTable::insert(const string& k, int d){
	int position = locate(k);					// find a insertion point
	if (position != -1){						// point is valid
		table[position] = new Record(k, d);		// insert data to index
		return true;							// success
	}
	return false;	// invalid point
};

/*
FIND FUNCTION
*/
int HashTable::find(const string &key) const{
	int index = locate(key);				// find the key
	if (index != -1)						// if found
		return table[index]->data;			// return the data
	else
		return -1;								// NOT FOUND
};

/*
DUMP FUNCTION
*/
void HashTable::dump() const{
	int size = table.size();						// initialize size variable
	cout << "HASH TABLE:\n######################\n";	// format
	for (int i = 0; i < size; i++){					// iterate through table
		cout << "INDEX: " << i;
		if (table[i] != nullptr){						// print index
			cout << "   KEY: " << table[i]->key			// print key
				<< "   DATA: "							// print data format
				<< table[i]->data << endl;			// print data
		}
		else
			cout << " HAS NOTHING THERE BRO. . .\n";			// no data
	}
};
