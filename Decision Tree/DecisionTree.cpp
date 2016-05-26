// DecisionTree.cpp : Defines the entry point for the console application.
//

/*
	NOTES:
		log2 (math.h) calculates log base 2
*/


#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <math.h>

using namespace std;

#pragma region Structures & Variables

#define LOAN_DATA

#ifdef LOAN_DATA
	#define NUM_ATTRIBUTES (4)
	#define NUM_EXAMPLES (14)
#else	// Restaurant data
	#define NUM_ATTRIBUTES (10)
	#define NUM_EXAMPLES (12)
#endif

#define MAX_ATTRIBUTE_VALUES (4)	// Maximum number of values for any given attribute
#define MAX_NAME_LENGTH (20)		// Maximum length of any string/name
#define MAX_TREE_CHILDREN (4)		// Maximum number of branches for any node in the tree

typedef struct {
	char AttributeName[MAX_NAME_LENGTH];		// Friendly name for this attribute
	unsigned char ExampleNdx;	// Index in Example array for this attribute
	unsigned char NumValues;	// Number of legal values for this attribute
	char ValueNames[MAX_ATTRIBUTE_VALUES][MAX_NAME_LENGTH];		// Friendly name for each value of this attribute
} ATTRIBUTE_STRUCT;

typedef struct {
	char Example[NUM_ATTRIBUTES][MAX_NAME_LENGTH];
	char GoalValue[MAX_NAME_LENGTH];
} EXAMPLE_STRUCT;


#ifdef LOAN_DATA
const ATTRIBUTE_STRUCT GoalAttribute = { "Loan?", 0, 2, "no", "yes" };				// Loan? is the goal attribute. Its values will be the labels for the leaf nodes of our tree

const ATTRIBUTE_STRUCT Attributes[NUM_ATTRIBUTES] = {
	{ "Credit History", 0, 3, "bad", "unknown", "good" },
	{ "Debt", 1, 2, "high", "low" },
	{ "Collateral", 2, 2, "none", "adequate" },
	{ "Income", 3, 3, "$0-$15k", "$15k-$35k", "over $35k" }
};

const EXAMPLE_STRUCT Examples[NUM_EXAMPLES] = {
	{{"bad", "high", "none", "$0-$15k"}, { "no" }},
	{{"unknown", "high", "none", "$15k-$35k"}, { "no" }},
	{{"unknown", "low", "none", "$15k-$35k"}, { "yes" }},
	{{"unknown", "low", "none", "$0-$15k"}, { "no" }},
	{{"unknown", "low", "none", "over $35k"}, { "yes" }},
	{{"unknown", "low", "adequate", "over $35k"}, { "yes" }},
	{{"bad", "low", "none", "$0-$15k" }, { "no" }},
	{{"bad", "low", "adqueate", "over $35k"}, { "no" }},
	{{"good", "low", "none", "over $35k" }, { "yes" }},
	{{"good", "high", "adequate", "over $35k"}, { "yes" }},
	{{"good", "high", "none", "$0-$15k"}, { "no" }},
	{{"good", "high", "none", "$15k-$35k"}, { "yes" }},
	{{"good", "high", "none", "over $35k"}, { "yes" }},
	{{"bad", "high", "none", "$15k-$35k"}, { "no" }}
};

#else	// Restaurant data
 
const ATTRIBUTE_STRUCT GoalAttribute = { "Eat?", 0, 2, "no", "yes" };

// Attribute Information
const ATTRIBUTE_STRUCT Attributes[NUM_ATTRIBUTES] = {
	{ "Alternative?", 0, 2, "no", "yes" },
	{ "Bar?", 1, 2, "no", "yes" },
	{ "Friday?", 2, 2, "no", "yes" },
	{ "Hungry?", 3, 2, "no", "yes" },
	{ "Patrons?", 4, 3, "none", "some", "full" },
	{ "Price", 5, 3, "$", "$$", "$$$" },
	{ "Rain?", 6, 2, "no", "yes" },
	{ "Reservation", 7, 2, "no", "yes" },
	{ "Type", 8, 4, "french", "itialian", "thai", "burger"},
	{ "Wait", 9, 4, "0-10", "10-30", "30-60", ">60" }
};

// Table
const EXAMPLE_STRUCT Examples[NUM_EXAMPLES] = {
	{{ "yes", "no",  "no", "yes", "some", "$$$", "no",  "yes", "french", "0-10", }, { "yes" }},
	{{ "yes", "no",  "no", "yes", "full", "$",   "no",  "no",  "thai",   "30-60"}, { "no" }},
	{{ "no",  "yes", "no", "no",  "some", "$",   "no",  "no",  "burger", "0-10"  }, { "yes" }},
	{{"yes", "no",  "yes","yes", "full", "$",   "yes", "no",  "thai",   "10-30" }, { "yes" }},
	{{ "yes", "no",  "yes","no",  "full", "$$$", "no",  "yes", "french", ">60", }, { "no" }},
	{{"no",  "yes", "no", "yes", "some", "$$",  "yes", "yes", "italian","0-10"}, { "yes" }},
	{{ "no",  "yes", "no", "no",  "none", "$",   "yes", "no",  "burger", "0-10",}, { "no" }},
	{{ "no",  "no",  "no", "yes", "some", "$$",  "yes", "yes", "thai",   "0-10"}, { "yes" }},
	{{ "no",  "yes", "yes","no",  "full", "$",   "yes", "no",  "burger", ">60" }, { "no" }},
	{{ "yes", "yes", "yes","yes", "full", "$$$", "no",  "yes", "italian","10-30"}, { "no" }},
	{{ "no",  "no",  "no", "no",  "none", "$",   "no",  "no",  "thai",   "0-10"}, { "no" }},
	{{ "yes", "yes", "yes","yes", "full", "$",   "no",  "no",  "burger", "30-60" }, { "yes" }}
};
#endif

typedef enum { NodeEmpty, NodeLeaf, NodeAttribute } NODE_TYPE;

struct TREE_NODE {
	NODE_TYPE NodeType;		// Type of this node (NodeLeaf, NodeAttribute)
	int NodeValue;		// Index in main Attributes list for this attribute if "NodeAttribute" type OR 0=no, 1=yes for NodeLeaf
	TREE_NODE *Child[MAX_TREE_CHILDREN];	// Pointer to child node(s)
};

#pragma endregion

#pragma region Functions
// Create a new tree node
TREE_NODE *CreateNode(NODE_TYPE Type, int NodeValue) {
	TREE_NODE *newNode = new TREE_NODE;

	if (newNode) {
		newNode->NodeType = Type;
		newNode->NodeValue = NodeValue;

		for (unsigned i = 0; i < MAX_TREE_CHILDREN; i++) 
			newNode->Child[i] = NULL;
	}

	return newNode;
}

// Attach a child tree node to a parent node
void AddChild(TREE_NODE *pParent, TREE_NODE *childNode) {
	if (pParent) {
			// Look for empty child branch
		for (unsigned i = 0; i < MAX_TREE_CHILDREN; i++) {
			if (pParent->Child[i] == NULL) {	// Emtpy child node found
				pParent->Child[i] = childNode;
				break;
			}
		}
	}
}

// Print the entire tree on the console
void DisplayTree(TREE_NODE *Root, int Indent) {
	if (Root) {
		for (int j = 0; j < Indent; j++)
			printf(" ");

		if (Root->NodeType == NodeAttribute)
			printf("%s\r\n", Attributes[Root->NodeValue].AttributeName);

		for (int i = 0; i < MAX_TREE_CHILDREN; i++) {
			if (Root->Child[i]) {
				for (int j = 0; j < Indent; j++)
					printf(" ");

				printf("   %s\r\n", Attributes[Root->NodeValue].ValueNames[i]);
				if (Root->Child[i]->NodeType == NodeLeaf) {
					for (int j = 0; j < Indent; j++)
						printf(" ");

					if (Root->Child[i]->NodeValue == 0) printf("      no\r\n");
						else printf("      yes\r\n");
				}
				else DisplayTree(Root->Child[i], Indent + 6);
			}
		}
	}
}

// Return the goal value (0=no, 1=yes) that occurs most frequently in the given Examples, choose randomly if counts are equal
int PluralityValue(vector<EXAMPLE_STRUCT> Examples) {
	int Counts[MAX_ATTRIBUTE_VALUES];
	int NumValues = GoalAttribute.NumValues;

		// Initialize counts to zero
	for (int i = 0; i < MAX_ATTRIBUTE_VALUES; i++) 
		Counts[i] = 0;

	for (unsigned i = 0; i < Examples.size(); i++) {
		int ndx;

			// Find the index of the value for this example's goal attribute
		for (ndx = 0; ndx < NumValues; ndx++)
			if (strcmp(Examples[i].GoalValue, GoalAttribute.ValueNames[ndx]) == 0) break;

		if (ndx < NumValues)
			Counts[ndx]++;

	}

	// Determine which value for the goal attribute has the highest count
	int Max = 0;
	int MaxNdx = 0;
	int MaxCount = 0;
	for (int i = 0; i < NumValues; i++)
		if (Counts[i] > Max) {	// Found new max
			Max = Counts[i];
			MaxNdx = i;
			MaxCount = 1;
		}
		else if (Counts[i] == Max)	// Other values found with the same value as max
			MaxCount++;

	if (MaxCount > 1) {	// Multiple counts exist with the same value
		int Ndx = rand() % NumValues;

			// Pick the Ndx Max value
		MaxCount = 0;
		for (int i = 0; i < NumValues; i++)
			if (Counts[i] == Max) {
				MaxCount++;
				if (MaxCount == (Ndx+1)) {	// We randomly pick this one
					MaxNdx = i;
					break;
				}
			}
	}

	if (strcmp(GoalAttribute.ValueNames[MaxNdx], "no")) return 0;
		else return 1;
}

// Determine if all Examples have the same goal value, if so, return true. The goal value (0=no, 1=yes) itself is returned through a parameter
unsigned char IsSameGoal(vector<EXAMPLE_STRUCT> Examples, int &GoalValue) {
	char *FirstGoalValue = Examples[0].GoalValue;

	unsigned i;
	for (i = 0; i < Examples.size(); i++)
		if (strcmp(FirstGoalValue, Examples[i].GoalValue) != 0) break;

	if (strcmp(FirstGoalValue, "no") == 0) GoalValue = 0;
		else GoalValue = 1;

	if (i < Examples.size()) return 0;	// Different goal values found
		else return 1;	// All examples have same goal value
}

// Count the number of examples that have the given attribute value
//  ExampleNdx is the column (attribute) in the example data to use for counting. Each column represents a specific attribute
int CountValues(int ExampleNdx, const char *ValueName, vector<EXAMPLE_STRUCT> Examples) {
	int Count = 0;

	for (unsigned i = 0; i < Examples.size(); i++) {
		if (strcmp(ValueName, Examples[i].Example[ExampleNdx]) == 0)
			Count++;
	}

	return Count;
}

// Count the number of examples that have "yes" for a goal for the given attribute value
//  ExampleNdx is the column (attribute) in the example data to use for counting. Each column represents a specific attribute
//		ExampleNdx = -1 means all examples 
int CountGoalValues(int ExampleNdx, const char *ValueName, vector<EXAMPLE_STRUCT> Examples) {
	int Count = 0;

	for (unsigned i = 0; i < Examples.size(); i++) {
		if (ExampleNdx == -1) {
			if (strcmp(Examples[i].GoalValue, "yes") == 0)
				Count++;
		}
		else
		if (strcmp(ValueName, Examples[i].Example[ExampleNdx]) == 0) {
			if (strcmp(Examples[i].GoalValue, "yes") == 0)
				Count++;
		}
	}

	return Count;
}

// Calculate the entropy for a two-valued property based on the probability that one of the values will occur
double CalculateBooleanEntropy(double probability) {
	if (probability == 0.0 || probability == 1.0) return 0.0;
		else return -((probability * log2(probability)) + ((1-probability) * log2(1-probability)));
}

#pragma endregion

// TODO: implement this function
// Calculate the total entropy for a given attribute in the Examples list :: Remainder(Attribute)
// Parameters: AttributeNdx : int == Index of the Attibute
//			   Attributes : vector<ATTRIBUTE_STRUCT> == vector containing all Attribute structs
//			   Examples : vector<EXAMPLE_STRUCT> == Table
double CalculateEntropyForAttribute(int AttributeNdx, vector<ATTRIBUTE_STRUCT> Attributes, vector<EXAMPLE_STRUCT> Examples) {
	double Entropy = 0.0;
	// Hint: use the Countvalues, CountGoalValues, and CalculateBooleanEntropy functions
	int EIndex = Attributes[AttributeNdx].ExampleNdx;  // EG: yes or no
	char* AName = Attributes[AttributeNdx].AttributeName;
	// Calculate P+N
	int Y = CountValues(EIndex,AName,Examples); // Counts how many example values have the attribute "AName" at EIndex
	for (int i = 0; i < Examples.size(); i++) {											 // iterate through table rows
		for (int j = 0; j < Attributes[AttributeNdx].NumValues; j++)
		// If the name in the column matches the name of the attribute to check.
		if (Examples[i].Example[EIndex] == AName) { // find attribute to check
			int X = CountGoalValues(Attributes[AttributeNdx].ExampleNdx, AName, Examples);
		}
	}

	return Entropy;
}

//TODO: Validate this function
// Calculate the attribute that has the greatest information gain. Returns the index of that attribute in the Attributes list that has the highest information gain
int CalculateMaxGain(vector<ATTRIBUTE_STRUCT> Attributes, vector<EXAMPLE_STRUCT> Examples) {
	int MaxGainNdx = 0;
	double MaxGain = 0.0;
	for (int i = 0; i < Attributes.size(); i++) {
		double ProjectedGain = CalculateEntropyForAttribute(i, Attributes, Examples);
		if (MaxGain < ProjectedGain) {
			MaxGain = ProjectedGain;
			MaxGainNdx = i;
		}
	}
	return MaxGainNdx;
}

//TODO: Implement this function // LAST WORKED ON
TREE_NODE *CreateDecisionTree(vector<EXAMPLE_STRUCT> Examples, vector<ATTRIBUTE_STRUCT> Attributes, vector<EXAMPLE_STRUCT> ParentExamples) {

	TREE_NODE DTree = TREE_NODE();
	if (Examples.empty()) { PluralityValue(ParentExamples); } // return
	else if (Examples[0].Example[1][1]) {} // wrong
	else if (Attributes.empty()) { PluralityValue(Examples); }// return 
	else {}
	return NULL;
}

int _tmain(int argc, _TCHAR* argv[])
{
	srand((unsigned int)time(NULL));

		// Create initial example and attribute lists
	vector<EXAMPLE_STRUCT> ParentExamples;
	vector<ATTRIBUTE_STRUCT> InitialAttributes;

	for (int i = 0; i < NUM_EXAMPLES; i++)
		ParentExamples.push_back(Examples[i]);

	for (int i = 0; i < NUM_ATTRIBUTES; i++)
		InitialAttributes.push_back(Attributes[i]);

		// Create tree
	TREE_NODE *Root = CreateDecisionTree(ParentExamples, InitialAttributes, ParentExamples);

		// Display results
	DisplayTree(Root, 0);

	return 0;
}

