#include "graph.h"
#include "dijkstra.h"
#include <iostream>

//  Use first version for earlier pre-Vista Windows
//const char *FILENAME = ".\\graph1.txt";
const char *FILENAME = "./graph1.txt";

using namespace std;

int main()
{
    AdjacencyMatrix adj = load_matrix(FILENAME);
    print_matrix(adj);
    shortest_path(adj, 0);
	
	// TEST CASES ////////////////////////////////////////////
	cout << endl << endl << endl;
	FILENAME = "./graph2.txt";
	adj = load_matrix(FILENAME);
	print_matrix(adj);
	shortest_path(adj, 2);

	cout << endl << endl << endl;
	FILENAME = "./graph3.txt";
	adj = load_matrix(FILENAME);
	print_matrix(adj);
	shortest_path(adj, 3);
	
}
