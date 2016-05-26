//  File:   RelationProperties.cpp
//  Author: Rick Halterman

//  Tests the relation properties functions

#include "relprop.h"
#include <fstream>

using std::ostream;
using std::ifstream;
using std::cout;
using std::endl;
using std::make_pair;


//  Read in the elements that constitute a set and the 
//  ordered pairs that make up a relation on that set.
//  s is the set of elements to load
//  rel is the relation to load
//  in is the input file stream from which the pairs are to be read
bool read_relation(Set& s, Relation& rel, istream& in)
{
	char ch;
	int first, second;

	//  Read the set's cardinality
	int size;
	in >> size;

	//  Read in the elements of the set
	int elem;
	for (int i = 0; i < size; i++)
	{
		in >> elem;
		s.insert(elem);
	}
	
	//  Read in the ordered pairs
	while ( !in.eof() )
	{
		//  Read '<' first ',' second '>'
		in >> ch >> first >> ch >> second >> ch;
		//  Ensure the components of the ordered pair are indeed elements of the set
		auto missing = end(s);
		if ( s.find(first) != missing && s.find(second) != missing )
		{
			auto p = make_pair(first, second);
			rel.insert(p);
		}
		else
			return false;  //  Clients may check return value for a faulty data file
	}
	return true;
}



//  Displays the ordered pairs that comprise relation s
//  to output stream os.
ostream& operator<<(ostream& os, const Relation& s)
{
	os << '{';
	if ( !s.empty() )
	{   //  Display the first element
		auto iter = begin(s);
		os << '<' << iter->first << ',' << iter->second << '>';
		iter++;
		//  Display the remaining elements, if any
		while ( iter != end(s) )
		{
			os << ',' << '<' << iter->first << ',' << iter->second << '>';
			iter++;
		}
	}
	os << '}';
	return os;
}

int main()
{
	Set S;
	Relation R;
	//  Read in the relation from a data file
	ifstream relfile("rel3.rel");
	if ( relfile.good() )
	{
		read_relation(S, R, relfile);
		relfile.close();
	}
	//  Display the relation
	cout << R << endl;
	//  Determine the properties of relation R
	cout << "Reflexive: " << is_reflexive(S, R) << endl;
	cout << "Symmetric: " << is_symmetric(R) << endl;
	cout << "Antisymmetric: " << is_antisymmetric(R) << endl;
	cout << "Transitive: " << is_transitive(R) << endl;
    
}
