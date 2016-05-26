//  Name: Matt Lucrida
//  Assignment number: 6
//  Assignment: Building a Binary Tree from Traversals
//  File name: treetrav.cpp
//  Date last modified: February 20, 2014
//  Honor statement: I have neither given nor received any unauthorized help on this assignment. 

#include <iostream>
#include <vector>

using namespace std;

/*
Preorder: First visit the node, then traverse the node's left subtree recursively, and finally traverse the node's right subtree recursively.
Inorder: Traverse the node's left subtree recursively, then visit the node, and finally traverse the node's right subtree recursively.
Postorder: Traverse the node's left subtree recursively, then traverse the node's right subtree recursively, and finally visit the node,
*/

/*Binary tree node*/
template <typename T> 
struct Node { 
	T data; 
	Node *left; 
	Node *right; 
	Node(const T& d, Node *lf, Node *rt) : 
		data(d), left(lf), right(rt) {} 
};


/*Function that constructs a binary tree (recursively)*/
template <typename T> 
Node<T> *build_tree(typename vector<T>::iterator pre_begin, typename vector<T>::iterator pre_end,
	typename vector<T>::iterator in_begin, typename vector<T>::iterator in_end) {
	Node<T> *create = new Node<T>(*pre_begin, nullptr, nullptr);	
	auto root = find(in_begin, in_end, *pre_begin);							// root location
	int boundary = distance(in_begin, root);								// find the matching number and log indices
	if ((pre_begin == (pre_end - 1)) && (in_begin == (in_end - 1)))			// checks if the node has no children
		return create;
	else if (root == (in_end - 1))																						// if the root is located at the end of the vector
		create->left = build_tree<T>(pre_begin + 1, (pre_begin + boundary + 1), in_begin, (in_begin + boundary));		// create JUST the vector with boundaries for the left subtree				
	else if (root == (in_begin))																						// if the root is located at the start of the vector
		create->right = build_tree<T>((pre_begin + boundary + 1), pre_end, (in_begin + boundary + 1), in_end);			// create JUST the vector with boundareis for the right subtree
	else{																												// Node has BOTH left and right children
		create->left = build_tree<T>(pre_begin + 1, (pre_begin + boundary + 1), in_begin, (in_begin + boundary));		// create the vector boundaries for the left subtree
		create->right = build_tree<T>((pre_begin + boundary + 1), pre_end, (in_begin + boundary + 1), in_end);			// create the vector boundareis for the right subtree
	}
	return create;
}


/*Function that prints the binary tree (sideways)*/
template <typename T> 
void draw(Node<T> *tree, char link, int depth) { 
	if (tree){											// if the pointing to a node that has data, and not a null pointer
		draw(tree->right, '/', depth+1);				// draw the right sub tree recursively
		for (int i = 0; i < depth; i++)					// depth formatting
			cout << "   ";								// 3 spaces
		cout << link << '[' << tree->data << "]\n";		// print out the node
		draw(tree->left, '\\', depth+1);				// draw the left sub tree recursively
	}
} 

template <typename T> 
void draw(Node<T> *tree) { 
	draw(tree, '-', 0); 
}
/*TEST main()*/
//int main() {
	// Specify a preorder and inorder traversal 
//	vector<int> pre = { 36, 100, 11, 3, 10, 5, 2, 8 },
//		in = { 11, 100, 10, 3, 5, 36, 8, 2 };
	// Build the binary tree from the traversals 
//	Node<int> *tree = build_tree<int>(begin(pre), end(pre), begin(in), end(in));
	// Draw the resulting tree 
//	draw(tree);
//}