#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_

#include "graph.h"

//  Used by Dijkstra's algorithm to determine the shortest path
struct VertexInfo
{
    int distance;  //  Current distance estimate
    bool known;    //  True, if the distance is truly minimal
    int previous;  //  Previous node on the path from the start
    VertexInfo();  //  Initializes a VertexInfo object
};

//  Used to maintain a list of VertexInfo objects for Dijkstra's
//  algorithm
typedef vector<VertexInfo> VertexList;

//  Computes the shortest path from the given start vertex
//  to all other vertices in the graph represented by the
//  given adjacency matrix.
VertexList dijkstra(AdjacencyMatrix m, int start);

//  Calls the dikstra function and reports the results.
void shortest_path(AdjacencyMatrix m, int start);

#endif
