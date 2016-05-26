//  Name: Matt Lucrida
//  Assignment number: 7
//  Assignment: Huffman Coding tree
//  File name: huffman.cpp
//  Date last modified: March 10, 2014
//  Honor statement: I have neither given nor received any unauthorized help on this assignment. 

#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

/*
Some code used here has been modified from assignment 6
*/

/*Huffman tree node*/
template <typename T>
struct Node {
	float data;									// data will be frequency
	T letter;									// stores the letter (if there is one)
	Node *left;
	Node *right;
	Node(float d, T l, Node *lf, Node *rt) :	
		data(d),letter(l), left(lf), right(rt) {}
};

/*comparison done for the priority queue*/
template <typename T>
struct comparison{
	bool operator() (Node<T> *first, Node<T> *second){		// first two elements in the priority queue
		return (first->data > second->data);					// returns boolean result
	}
};

/*Function that prints the tree (sideways)*/
template <typename T>
void draw(Node<T> *tree, char link, int depth) {
	if (tree){											// if the pointing to a node that has data, and not a null pointer
		draw(tree->right, '/', depth + 1);				// draw the right sub tree recursively
		for (int i = 0; i < depth; i++)					// depth formatting
			cout << "    ";								// 4 spaces
		if (tree->letter != NULL){
			cout << link << '[' << tree->letter << ":" << tree->data << "]\n";		// print formatting if there is a letter
		}
		else{
			cout << link << '(' << tree->data << ")\n";								// print formatting if there isn't a letter
		}
		draw(tree->left, '\\', depth + 1);				// draw the left sub tree recursively
	}
}

/*initial draw function*/
template <typename T>
void draw(Node<T> *tree) {
	draw(tree, '-', 0);
}

/*huffman tree logic*/
template <typename T>
Node<T> *create_forest(priority_queue<Node<char>*, vector<Node<char>*>, comparison<char>> leaf){
	while (leaf.size() > 1){																			// while not at the root node
		Node<T> *left_child = leaf.top(); leaf.pop();													// get the first node and pop it off
		Node<T> *right_child = leaf.top(); leaf.pop();													// get the second node and pop it off
		leaf.push(new Node<char>((left_child->data + right_child->data), NULL, left_child, right_child));// push the new node back into the priority queue
	}
	return leaf.top();		// return the root node
}

/*huffman encoding logic*/
template <typename T>
void encode(Node<T> *forest, string binary){
	if (forest != nullptr){											// while there are more children
		encode(forest->left, binary + '0');							// recurse left and append 0 to the code
		encode(forest->right, binary + '1');						// recurse right and append 1 to the code
		if (forest->letter != NULL)									// if the node is a letter
			cout << forest->letter << ": " << binary << endl;		// print it out with the code
	}

}

int main() {
	int alphabet[26] = {};					// array that will contain the frequency of each occurance of a letter in the alphabet 
	int total = 0;							// contains all the characters
	while (cin.good()){						// while the file still has characters
		char letter = char(cin.get());		// read the character
		cout << letter;						// print the character
		letter = char(toupper(letter));		// convert it to upercase
		if (65 <= letter && letter <= 90){	// if the character is a letter
			alphabet[letter - 65]++;		// increment the frequency of that letter
			total++;						// increment the total letters
		}
	}
	priority_queue<Node<char>*, vector<Node<char>*>, comparison<char>> leaves;	// priority queue decleration
	cout << "Counts:\n-------\n";
	char label = 65;									// start label at A
	for (int i = 0; i < 26; i++){						// itterate through the alphabet array
		cout << label << ": " << alphabet[i] << endl;	// print the label and the frequency
		leaves.push(new Node<char>(float(alphabet[i]) / float(total),label, nullptr, nullptr)); // initialize leaves
		label++;										// change the label to the next letter in the alphabet
	}
	cout << "Total = " << total << "\n\n---------------------------------\n";	// print total and section break
	Node<char> *nature = create_forest<char>(leaves);							// creates the forest
	draw(nature);																// draws the forest
	cout << "\n\n---------------------------------\n";							// section break
	encode(nature, "");															// huffman encode the forest
}