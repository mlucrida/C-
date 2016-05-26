#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

typedef vector< vector<int> > AdjacencyMatrix;

extern const int INF;  //  Represents infinity


//  Represents a non-matrix. Useful for 
//  when an adjacency matrix is required
//  but for some reason the necessary matrix
//  is not available.
extern const AdjacencyMatrix NO_MATRIX;

//  Reads an adjacency matrix from a textfile.
//  Returns NO_MATRIX if an adjacency matrix 
//  cannot be made.
AdjacencyMatrix load_matrix(const char *filename);

//  Makes graph consisting of a forest of n single 
//  vertex trees.
AdjacencyMatrix make_empty(int n);

//  Display the adjacency matrix
void print_matrix(AdjacencyMatrix m);


#endif
