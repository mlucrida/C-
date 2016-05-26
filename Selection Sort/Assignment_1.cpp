/*
	File:	Assignment_1.cpp (Selection Problem)
	Author:	Matt Lucrida
	Date:	1/14/2014
	*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include <functional>
#include "stopwatch.h"

using namespace std;

/*
	NOTE: list data is formated: N k n1 n2 n3 where
	# N is the number of integers to be considered (size)
	# k corresponds to k in the problem
	# n1,n2,n3 is where the actual values begin.

	also, the list contains no dupilactes.

	RUN IN RELEASE MODE

	*/
double select_kth_largest1(std::istream& in){			// sort and select
	// #######################
	// # SETUP/INITILIZATION #
	// #######################
	int size;	in >> size;								// size of list
	int k;		in >> k;								// the k element
	vector<double> vec(size);							// declares a vector
	for (int i = 0; i < size; i++)
		in >> vec[i];									// fills the vector

	// ###########
	// # PROCESS #
	// ###########
	sort(vec.begin(), vec.end(), greater<double>());	// sort the vector in decending order
	return vec[k - 1];									// returns the k-1 element of the sorted vector
}

double select_kth_largest2(std::istream& in){			// partial sort and insert

	// #######################
	// # SETUP/INITILIZATION #
	// #######################
	int size;	in >> size;								// size of the entire list
	int k;		in >> k;								// the k element
	vector<double> vec_k(k);							// declares the sorted vector (of k elements)
	for (int i = 0; i < k; i++)
		in >> vec_k[i];									// vec_k initialization

	int vec_size = size - k;							// the number of remaining elements
	vector<double> vec(vec_size);						// declares the remaining vector
	for (int i = 0; i < vec_size; i++)
		in >> vec[i];									// vec initialization

	// ###########
	// # PROCESS #
	// ###########
	sort(vec_k.begin(), vec_k.end(), greater<double>());				// sort vec_k in decending order.
	for (int check_index = 0; check_index < vec_size; check_index++){	// itterate through vec
		if (vec_k[k - 1] < vec[check_index]){							// TRUE: if the element is bigger than the smallest element in vec_k
			for (int i = 0; i < k; i++){								// inserts the element to its appropriate index
				if (vec[check_index] > vec_k[i]){
					vec_k.pop_back();									// make room for the new number
					vec_k.insert(i + vec_k.begin(), vec[check_index]);	// insert to vec_k from vec
					i = k;												// i is set to k to break out of loop because break statements are EVIL
				}
			}
		}
	}
	return vec_k[k - 1];

}
int main() {
	Stopwatch clock;									// Stopwatch declaration
	for (int i = 0; i < 10; i++){		// main process is tested 10 times to get an average execution time (See Timing_Table.xlsx)
		cout << "PROCESS: " << i+1 << "---------------------------------------------------------------------\n";
		//----FILE USED: data 100.txt--------------------------------------------------------------------------------------------------------
		ifstream fin("data_100.text");						// ifstream declaration and selecting file
		if (fin.good()){									// check if successful open
			cout << "data_100.text:\n";						// format
			cout << "SORT AND SELECT METHOD: " << setw(11);	// format

			clock.start();						// clock starts
			cout << select_kth_largest1(fin);	// start function
			clock.stop();						// clock stops

			cout << setw(9) << " TIME: " << clock.elapsed() << " seconds" << endl; // print time

			clock.reset();						// reset clock
			fin.clear();						// clears fin					
			fin.seekg(0, ios::beg);				// goes back to the beginning of the file
			cout << "PARTIAL SORT AND INSERT METHOD: ";	// next method

			clock.start();						// clock start
			cout << select_kth_largest2(fin);	// starts function
			clock.stop();						// clock stops

			cout << setw(9) << " TIME: " << clock.elapsed() << " seconds" << endl << endl;	// pritn time

			clock.reset();						// reset
		}
		else
			cout << "could not open file: \"data 100.text\"\n";
		fin.close();

		/*
			next lines of code follow the same general pattern
			differences are only in print formatting and file read from
		*/

		//----FILE USED: data 1000.txt--------------------------------------------------------------------------------------------------------
		fin.open("data_1000.text");
		if (fin.good()){
			cout << "data_1000.text:\n";
			cout << "SORT AND SELECT METHOD: " << setw(12);

			clock.start();
			cout << select_kth_largest1(fin);
			clock.stop();

			cout << setw(8) << " TIME: " << clock.elapsed() << " seconds" << endl;

			clock.reset();
			fin.clear();						// clears fin					
			fin.seekg(0, ios::beg);				// goes back to the beginning of the file
			cout << "PARTIAL SORT AND INSERT METHOD: ";

			clock.start();
			cout << select_kth_largest2(fin);
			clock.stop();

			cout << setw(8) << " TIME: " << clock.elapsed() << " seconds" << endl << endl;

			clock.reset();
		}
		else
			cout << "could not open file: \"data 1000.text\"\n";
		fin.close();

		//----FILE USED: data 100000.txt--------------------------------------------------------------------------------------------------------
		fin.open("data_100000.text");
		if (fin.good()){
			cout << "data_100000.text:\n";
			cout << "SORT AND SELECT METHOD: " << setw(13);

			clock.start();
			cout << select_kth_largest1(fin);
			clock.stop();

			cout << " TIME: " << clock.elapsed() << " seconds" << endl;

			clock.reset();
			fin.clear();						// clears fin					
			fin.seekg(0, ios::beg);				// goes back to the beginning of the file

			cout << "PARTIAL SORT AND INSERT METHOD: ";

			clock.start();
			cout << select_kth_largest2(fin);
			clock.stop();

			cout << " TIME: " << clock.elapsed() << " seconds" << endl << endl;

			clock.reset();
		}
		else
			cout << "could not open file: \"data 100000.text\"\n";
		fin.close();


	}
}

//	#################
//	# EDDITOR NOTES #
//	#################
/*
	SUGGESTION: Template the main process.
	*/