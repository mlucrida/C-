#include "graph.h"
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <climits>  //  For INT_MAX


using namespace std;


//  Reads an adjacency matrix from a textfile.
//  Returns NO_MATRIX if an adjacency matrix 
//  cannot be made.
AdjacencyMatrix load_matrix(const char *filename)
{
    int number_of_vertices;
    //  Open file
    fstream fin(filename, ios::in);
    if ( fin.good() )
        {
        //  Read number of vertices
        fin >> number_of_vertices;
        //  Create the appropriately-sized matrix
        AdjacencyMatrix matrix = make_empty(number_of_vertices);
        //  Populate the adjacency matrix
        for ( int row = 0; row < number_of_vertices; row++ )
            for ( int col = 0; col < number_of_vertices; col++ )
            {
                int in_value;
                fin >> in_value;
                matrix[row][col] = (in_value == -1)? INF : in_value;
            }
        //  Close file
        fin.close();
        return matrix;
    }
    return NO_MATRIX;   //  Could not load the adjacency matrix
}

//  Makes graph consisting of a forest of n single 
//  vertex trees.
AdjacencyMatrix make_empty(int n)
{
    return AdjacencyMatrix(n, vector<int>(n, INF));
}


//  Display the adjacency matrix
void print_matrix(AdjacencyMatrix m)
{
    if ( m == NO_MATRIX )
        cout << "No adjacency matrix" << endl;
    else
        for ( unsigned row = 0; row < m.size(); row++ )
        {
            for ( unsigned col = 0; col < m[row].size(); col++ )
                if ( m[row][col] != INF )
                    cout << setw(3) << m[row][col];
                else
                    cout << setw(3) << '.';
            cout << endl;
        }
}

const AdjacencyMatrix NO_MATRIX;

const int INF = INT_MAX;
