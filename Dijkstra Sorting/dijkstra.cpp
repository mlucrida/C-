//  Name: Matt Lucrida
//  Assignment number: 10
//  Assignment: Dijkstra's Algorithm
//  File name: dijkstra.cpp
//  Date last modified: April 3, 2014
//  Honor statement: I have neither given nor received any unauthorized help on this assignment. 

#include "dijkstra.h"
#include <iostream>
#include <iomanip>

//  Constructor makes a VertexInfo object with an "infinite" 
//  distance estimate, shortest path unknown, and no previous vertex
//  on a shortest path from the start.
VertexInfo::VertexInfo(): distance(INF), known(false), previous(-1) {}


//  Computes the shortest path from the given start vertex
//  to all other vertices in the graph represented by the
//  given adjacency matrix.
/*  
list of nodes is initialized where all verticies have a distance of 
infinity from start node, smallest path is marked as false, 
and has no previous nodes
*/
VertexList dijkstra(AdjacencyMatrix m, int start)
{
	VertexList V(m.size());													// initialize list of nodes
	int size = m.size();													// save list size
	int check_node = start;													// intitialize starting check_node
	V[start].distance = 0;													// initialize start node distance as zero
	bool done = false;
	while (!done){
		V[check_node].known = true;												// set check_node's shortest path to known
		for (int i = 0; i < size; i++){											// iterate through nodes
			if (m[check_node][i] != INF && !V[i].known){						// if a linked node's shortest path isn't known
				int compared_dist = V[check_node].distance + m[check_node][i];	// caclulates a new path /* V[row].distance = distance of checked node; m[row][i] = distance to a linked node */
				if (compared_dist < V[i].distance){								// compare caluclated distance to current distance from start node
					V[i].distance = compared_dist;								// replace current distance if calculated distance is shorter
					V[i].previous = check_node;									// update the neighboring node's previous
				}
			}
		}
		int smallest = INF;							// intitialize smallest distance
		for (int i = 0; i < size; i++){				// iterate through list of nodes
			if (!V[i].known){						// check remaining nodes with unknown smallest distances
				if (V[i].distance < smallest){		// distance comparison
					smallest = V[i].distance;		// new distance to compare
					check_node = i;					// new check node
				}
			}
		}
		if (smallest == INF) // nothing changed, all distances are known
			done = true;
	}

    return V;
}

//  Prints the path to this node from the start.
static void print_path(VertexList V, int pos)
{
    if ( V[pos].previous != -1 )
    {
        print_path(V, V[pos].previous);
        std::cout << " -> " << pos;
    }
}

//  Calls the dikstra function and reports the results.
void shortest_path(AdjacencyMatrix m, int start)
{
    VertexList V = dijkstra(m, start);
    std::cout << "Node | Dist. | Path" << std::endl;
    std::cout << "-----+-------+--------" << std::endl;
    for ( unsigned i = 0; i < V.size(); i++ )
    {
        std::cout << setw(4) << i << " | " << setw(5) << V[i].distance << " | ";
        std::cout << start;
        print_path(V, i);
        std::cout << std::endl;
    }
}
