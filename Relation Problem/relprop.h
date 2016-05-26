#ifndef DEFINED_RELPROP_H_
#define DEFINED_RELPROP_H_

#include <set>
#include <iostream>

using std::istream;

//  Some convenient type names
typedef std::set<int> Set;
typedef std::pair<int, int> Pair;
typedef std::set<std::pair<int, int>> Relation;

//  Returns true if relation rel is reflexive;
//  otherwise, returns false
//  s is a set
//  rel is a relation, a subset of s x s
bool is_reflexive(const Set& s, const Relation& rel);

//  Returns true if relation rel is symmetric;
//  otherwise, returns false
bool is_symmetric(const Relation& rel);

//  Returns true if relation rel is antisymmetric;
//  otherwise, returns false
bool is_antisymmetric(const Relation& rel);

//  Returns true if relation rel is transitive;
//  otherwise, returns false
//  rel is a relation
bool is_transitive(const Relation& rel);


#endif
