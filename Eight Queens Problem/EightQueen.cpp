// EightQueen.cpp 
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

const int DIM = 8;
const int TEST_ITERS = 100;
const int CONSECUTIVE_THRESHOLD = 100;
const int MAX_COST = 28;
const int INITIAL_POPULATION_SIZE = 20;
const double MUTATE_PROBABILITY = 0.10;
const int GENETIC_MAX = 28;

typedef struct {
	int queens[DIM];	// row of each queen in the given column
} node;

	// Initialize state to empty and then add one queen per column
void CreateRandomState(node &state) {
	for (int col = 0; col < DIM; col++)
		state.queens[col] = rand() % DIM;
}

	// Display eightqueens board with "*" to represent queen
void DisplayState(node &state) {
	for (int col = 0; col < DIM; col++)
		cout << state.queens[col] << " ";
	cout << endl;

	for (int row = 0; row < DIM; row++)
	{
		for (int col = 0; col < DIM; col++)
			if (state.queens[col] == row) cout << "* ";
				else cout << "  ";
		
		cout << endl;
	}
}

bool isAttack(int col1, int row1, int col2, int row2) {
	if (row1 == row2) return true;		// Same row

	if (row1 + (col2 - col1) == row2) return true;		// Diagonal down

	if (row1 - (col2 - col1) == row2) return true;		// Diagonal up

	return false;
}

int CalculateAttackingQueens(node &state) {
	int retCount = 0;

	for (int col = 0; col < DIM; col++) {
		for (int attackCol = col + 1; attackCol < DIM; attackCol++) {
			if (isAttack(col, state.queens[col], attackCol, state.queens[attackCol]))
			{
				retCount++;
			}
		}
	}

	return retCount;
}

bool IsStateEqual(node state1, node state2) {
	bool same = true;

	for (int i = 0; i < DIM; i++)
		if (state1.queens[i] != state2.queens[i]) same = false;

	if (same) return true;
	else
		return false;
}

bool InClosedList(node state, vector<node>& closedList) {

	for (vector<node>::iterator it = closedList.begin(); it != closedList.end(); ++it) {
		if (IsStateEqual(*it, state)) return true;
	}
	return false;
}

node CalcBestSuccessor(node &state) {
	int minAttacks = 1000;
	vector<node> minStateList;
	

	for (int col = 0; col < DIM; col++) {
		for (int row = 0; row < DIM; row++) {
			node testState = state;
			testState.queens[col] = row;

			int attacks = CalculateAttackingQueens(testState);

			if (attacks < minAttacks) {
				minStateList.clear();
				minStateList.push_back(testState);
				minAttacks = attacks;
			}
			else if (attacks == minAttacks) {		// Keep list of equal minimums
				minStateList.push_back(testState);
			}
		}
	}

	node minState;

	if (minStateList.size() == 1)
		minState = minStateList[0];
	else
		minState = minStateList[rand() % minStateList.size()];

	return minState;
}

node GetRandomSuccessor(node &state) {
	int col = rand() % DIM;
	int row;

	do
	row = rand() % DIM;
	while (row == state.queens[col]);

	node retNode = state;

	retNode.queens[col] = row;

	return retNode;
}

node SolveHillClimbingShoulder(node &initialState) {
	node retValue = initialState;

	// TODO Implement this (InClass #6)

	return retValue;
}

node SolveHillClimbing(node &initialState) {
	node retValue = initialState;

	// TODO Implement this (InClass #6)

	return retValue;	// TODO - Replace this with your solution
}

double CalculateAcceptanceProbability(int currentValue, int newValue, double T) {
	double p = exp((newValue - currentValue) / (double) MAX_COST / T);

	if (p > 1.0) p = 1.0;

	return p;
}

node SimulatedAnnealing(node& initialState) {
	node retValue = initialState;

	// TODO Implement this (InClass #6)

	return retValue;
}

int GeneticFitnessFunction(node state) {
	return MAX_COST - CalculateAttackingQueens(state);
}

node GeneticFindBestState(vector<node>& population) {
	node best = population[0];
	int bestScore = GeneticFitnessFunction(best);

	for (unsigned i = 1; i < population.size(); i++)
	{
		int score = GeneticFitnessFunction(population[i]);
		if (score > bestScore) {
			best = population[i];
			bestScore = score;
		}
	}

	return best;
}

void GeneticCreatePopulation(vector<node>& population) {
	// TODO Implement this (InClass #7)
}

node GeneticSelect(vector<node>& population) {
	// TODO Implement this (InClass #7)
	return population[0];	// This is just temporary (to make everything compile) and will not be used this way in your solution
}

node GeneticReproduce(node x, node y) {
	node child = x;	// This is just temporary and will not be used this way in your solution

	// TODO Implement this (InClass #7)

	return child;
}

node GeneticMutate(node child) {
	// TODO Implement this (InClass #7)
	return child;
}

/* TODO (InClass #7 - Implement genetic algorithm)
node GeneticAlgorithm() {
	
}
*/

void RunTestsWithStats() {
	node initialState;
	int attacks = 0;
	clock_t begin;
	clock_t end;

	begin = clock();
	int solved = 0;
	for (int i = 0; i < TEST_ITERS; i++) {
		CreateRandomState(initialState);

		attacks = CalculateAttackingQueens(SolveHillClimbing(initialState));

		if (attacks == 0) solved++;
	}
	end = clock();

	cout << "Hill Climbing - Solved " << solved / (double) TEST_ITERS << " in " << ((double)(end - begin) / CLOCKS_PER_SEC) << " seconds" << endl;
	
	begin = clock();
	solved = 0;
	for (int i = 0; i < TEST_ITERS; i++) {
		CreateRandomState(initialState);

		attacks = CalculateAttackingQueens(SolveHillClimbingShoulder(initialState));

		if (attacks == 0) solved++;
	}
	end = clock();

	cout << "Hill Climbing with sidways move - Solved " << solved / (double) TEST_ITERS << " in " << ((double)(end - begin) / CLOCKS_PER_SEC) << " seconds" << endl;

	begin = clock();
	solved = 0;
	for (int i = 0; i < TEST_ITERS; i++) {
		CreateRandomState(initialState);

		attacks = CalculateAttackingQueens(SimulatedAnnealing(initialState));

		if (attacks == 0) solved++;
	}
	end = clock();

	cout << "Simulated Annealing - Solved " << solved / (double) TEST_ITERS << " in " << ((double)(end - begin) / CLOCKS_PER_SEC) << " seconds" << endl;

	/* TODO - uncomment this when ready to test genetic algorithm
	begin = clock();
	solved = 0;
	for (int i = 0; i < TEST_ITERS; i++) {
		attacks = CalculateAttackingQueens(GeneticAlgorithm());

		if (attacks == 0) solved++;
	}
	end = clock();

	cout << "Genetic Algorithm - Solved " << solved / (double) TEST_ITERS << " in " << ((double)(end - begin) / CLOCKS_PER_SEC) << " seconds" << endl;
	*/

}

int _tmain(int argc, _TCHAR* argv[])
{
	srand((unsigned int) time(NULL));

	RunTestsWithStats();

	return 0;
}

