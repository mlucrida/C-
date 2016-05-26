//  Name: Matt Lucrida
//  Assignment number: 2
//  Assignment: Relation Properties
//  File name: relprop.cpp
//  Date last modified: January 21, 2014
//  Honor statement: I have neither given nor received any unauthorized help on this assignment.

#include <iostream>

#include "relprop.h"
using namespace std;
/*
###############################################
#  Returns true if relation rel is reflexive; #
#  otherwise, returns false					  #
#  s is a set								  #
#  rel is a relation, a subset of s x s		  #
###############################################
*/

bool is_reflexive(const Set& s, const Relation& rel){

	for (auto element = s.begin(); element != s.end(); ++element){		// iterates through the set elements
		if (rel.find(Pair{*element,*element}) == rel.end())				// looks for a reflexive relation based on the elements
			return false;												// if it's one is missing, then it cannont be reflexive
	}
	return true;														// all elements have a reflexive relation
};
/*
###############################################
# Returns true if relation rel is symmetric;  #
# otherwise, returns false					  #
# (only takes in 1 parameter: paired set) 	  #
###############################################
*/
bool is_symmetric(const Relation& rel){
	for (auto REL = rel.begin(); REL != rel.end(); ++REL){				// iterates through the set relations
		if (REL->first != REL->second){									/* given <a,b> if a == b the relation is symmetric to itself,
																		   but if not then. . . . */
			if(rel.find(Pair{ REL->second, REL->first }) == rel.end())	// the pair is swapped and then looked for, if not found then. . .
				return false;											// the set relations are not symmetric
		}																// if not found, then set relations can still be possibly symmetric
	}
	return true;														// all given relations are symmetric 
};
/*
################################################### 
# Returnes true if relation rel is antisymmetric; #
# otherwise, returns false						  #
# (only takes in 1 parameter: paired set)		  #
# ################################################# 
*/
bool is_antisymmetric(const Relation& rel){
	for (auto REL = rel.begin(); REL != rel.end(); ++REL){				// iterates through the set relations
		if (REL->first != REL->second){									/* given <a,b> if a == b the relation is antisymmetric to itself,
																		but if not then. . . . */
			if (rel.find(Pair{ REL->second, REL->first }) != rel.end())	// the pair is swapped and then looked for, if not found then. . .
				return false;											// if found then the set relations are not  antiseymmetric
		}																// if not found, then set relations can still be possibly antisymmetric
	}
	return true;														// all given relations are antisymmetric 
};
/*
############################################### 
# Returns true if relation rel is transitive; #
# otherwise, returns false					  #
# rel is a relation							  #
###############################################
*/
bool is_transitive(const Relation& rel){
	for (auto REL_i = rel.begin(); REL_i != rel.end(); ++REL_i){				// iterate through set relations
		for (auto REL_j = rel.begin(); REL_j != rel.end(); ++REL_j){			// iterate through set relations compared
			if (REL_i->second == REL_j->first){									// if an aRb bRc relation is found. . . .
				if (rel.find(Pair{ REL_i->first, REL_j->second }) == rel.end())	// look for an aRc relation
					return false;												// if not found, then set relations are not transitive
			}																	// look for more relations 
		}																		// all compared relations have passed
	}																			
	return true;																// all given relations are transitive
};