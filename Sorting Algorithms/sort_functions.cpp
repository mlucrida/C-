//  Name: Matt Lucrida
//  Assignment number: 8
//  Assignment: Sort Comparison
//  File name: sort_functions.cpp
//  Date last modified: 24 March 2014
//  Honor statement: I have neither given nor received any unauthorized help on this assignment.

#include <iostream>	
#include <vector>	
#include <stdlib.h>	
#include <ctime>	
#include <utility>	
#include <algorithm>	
#include <functional>	
#include "stopwatch.h"	
using namespace std;

// all vectors will be sorted in ascending order
// run the program in release mode for faster performance

/*
PRINTING FUNCTION DOESN'T WORK PROPERLY, MAY HAVE TO CALL BY REFERENCE
QUICKSORT CRASHES PROGRAM
*/
template<typename T>
bool sorted(vector<T>& vec, int size){
	for (int index = 0; index < size - 1; index++){
		if (vec[index] > vec[index + 1]){
			cout << "\n## NOT SORTED ##\n";
			return false;
		}
	}
	cout << "\n## SORTED ##\n";
	//	vec_print(vec, size);
	return true;
}

/*print function call*/
template<typename T>
void vec_print(vector<T>& vec, int size){
	int index = 0;								// initialize index
	cout << "VECTOR[" << size << "]: {";		// FORMATING
	for (; index < size - 1; index++){			// iteration
		cout << vec[index] << ", ";				// printing
	}
	cout << vec[index] << "}\n" << endl;			// FORMATING
}

/*
function to fill vector with a desired amount of random integers < 100000
*/
template<typename T>
int fill_vector(vector<T>& vec){
	int size;									// initialize
	cout << "input desired size of vector: ";	// user prompt
	cin >> size;								// user input
	srand(static_cast<unsigned>(time(0)));		// generate random number
	for (int i = 0; i < size; i++){				// iterations
		vec.push_back(rand() % 101);			// fill vector
	}
	cout << "\n## DONE ##\n";					// completed
	//	vec_print(vec, size);						// prints the vector
	return size;
}

/*
selection sort: increments through the entire vector
and places the correct number at a given index after
comparing all the numbers in the vector to it.  itterates
through the entire vector until the process is completed
*/
template<typename T>
void selection_sort(vector<T>& vec, int size){
	for (int i = 0; i < size; i++){			// check loop
		int smallest = i;					// index to be compared
		for (int j = i; j < size; j++){		// comparison loop
			if (vec[smallest] > vec[j])		// if the checked value is larger than the compared value
				smallest = j;				// set new smallest value to be checked and compared
		}
		swap(vec[smallest], vec[i]);		// swap after comparison iteration is complete
	}
	sorted(vec, size);						// function to confirm the vector is sorted

}

/*
insertion sort: compares the data of two values in
and shifts larger values to the right until the checked
data is inserted into it's appropriate spot. Repreat
process through the entire vector until it is completely
sorted.
*/
template<typename T>
void insertion_sort(vector<T>& vec, int size){
	for (int i = 0; i < size; i++){						// iterate through the vector
		int index = i;									// save checked index
		T data = vec[i];								// and save checked data
		while (index != 0 && vec[index - 1] > data){	// shift comparison 
			vec[index] = vec[index - 1];				// shift data
			index--;									// decrement checked indices
		}
		vec[index] = data;								// insert checked data to it's spot
	}
	sorted(vec, size);									// function to confirm the vector is sorted

}
/*
quicksort call; mainly used for printing purposes
*/
template<typename T>
void quicksort(vector<T>&vec, int size){
	quicksort(vec, 0, size - 1);						// sorting call
	sorted(vec, size);									// function to confirm the vector is sorted
}
/*
quicksort: partitions the vector at a given pivot point
and places all smaller values to the left and all larger
values to the right, repreat the process recursively
until the vector has been competely sorted (one number
for each partition).
*/
template<typename T>
void quicksort(vector<T>& vec, int start_index, int end_index){
	if (start_index < end_index){					// if partition is more than one element
		T pivot = vec[start_index];					// pivot value
		int p_check = start_index;					// compared index //becomes -1
		int check = start_index;					// initialize index to be compared
		swap(vec[start_index], vec[end_index]);		// move comparision value to the end of the partition
		while (check != end_index){					// iterate through partition
			if (pivot >= vec[check]){				// if the checked value is smaller than the pivot value
				swap(vec[p_check], vec[check]);		// move it to the left side of the vector
				p_check++;							// increment the pivot index
			}
			check++;								// increment the check index
		}
		swap(vec[p_check], vec[end_index]);			// place the partition back in it's correct spot // THIS SWAP SCREWS THINGS UP
		quicksort(vec, start_index, p_check - 1);	// recurse left partition
		quicksort(vec, p_check + 1, end_index);		// recurse right partition
	}
}
/*comparison function for qsort call*/
int comparison(const void *val1, const void *val2){
	return (*(int*)val1 - *(int*)val2);
	/*
	if val1 < val2, returns a negative value
	if val1 == val2, returns zero
	if val1 > val2, returns a positive value
	*/
}

/* MAIN */
int main() {
	bool still_going = true;		// initialize boolean variable
	char response;					// initialize response variable
	Stopwatch clock;				// initialize stopwatch
	vector<int> vec;				// initialize vector
	//	vector<int> TESTER{ 35, 81, 0, 73, 34 };
	while (still_going){			// keeps going until user decides to quit
		int vector_size = fill_vector<int>(vec);		// fill the vector with random numbers
	
/*
#############
# SORT CALL #
#############
*/		
		clock.reset();					// reset stopwatch
		clock.start();					// start stopwatch
		sort(vec.begin(), vec.end());	// sort call
		clock.stop();					// stop stopwatch
		cout << "VECTOR[" << vector_size << "] SORT TIME: " << clock.elapsed() << endl << endl;	// report time
		random_shuffle(vec.begin(), vec.end());									// reshuffle vector
//			vec_print(vec, vector_size);

/*
##############
# QSORT CALL #
##############
*/
		clock.reset();											// reset stopwatch
		clock.start();											// start stopwatch
		qsort(&vec[0], vector_size, sizeof(int), comparison);	// qsort call
		clock.stop();											// stop stopwatch
		cout << "VECTOR[" << vector_size << "] QSORT TIME: " << clock.elapsed() << endl << endl;	// report time
		random_shuffle(vec.begin(), vec.end());					// reshuffle vector
//			vec_print(vec, vector_size);

/*
#######################
# SELECTION_SORT CALL #
########################
*/
		clock.reset();							// reset stopwatch
		clock.start();							// start stopwatch
		selection_sort<int>(vec, vector_size);	// selection sort call
		clock.stop();							// stop stopwatch
		cout << "VECTOR[" << vector_size << "] SELECTION_SORT TIME: " << clock.elapsed() << endl << endl;	// report time
		random_shuffle(vec.begin(), vec.end());									// reshuffle vector
//			vec_print(vec, vector_size);

/*
#######################
# INSERTION_SORT CALL #
#######################
*/

		clock.reset();							// reset stopwatch
		clock.start();							// start stopwatch
		insertion_sort<int>(vec, vector_size);	// insertion sort call
		clock.stop();							// stop stopwatch
		cout << "VECTOR[" << vector_size << "] INSERTION_SORT TIME: " << clock.elapsed() << endl << endl;	// report time
		random_shuffle(vec.begin(), vec.end());									// reshuffle vector
//			vec_print(vec, vector_size);

/*
#######################
# QUICKSORT_SORT CALL #
#######################
*/

		clock.reset();							// reset stopwatch
		clock.start();							// start stopwatch
		quicksort<int>(vec, vector_size);		// quicksort function call
		clock.stop();							// stop stopwatch
		cout << "VECTOR[" << vector_size << "] QUICKSORT TIME: " << clock.elapsed() << endl << endl;
		random_shuffle(vec.begin(), vec.end());									// reshuffle vector
//			vec_print(vec, vector_size);


		cout << "to quit press 'q'\nto keep going, use any other key\n";		// user prompt
		cin >> response;			// user input
		if (response == 'q')		// if user decides to quit
			still_going = false;	// change boolean variable
	}
}