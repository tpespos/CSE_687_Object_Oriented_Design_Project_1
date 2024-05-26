#pragma once

// Syracuse University
// CSE 687 Object Oriented Design

#include <iostream> // debug purposes
#include "File_Management.h"
#include <vector>
#include <string>
#include <sstream>
using std::string;
using std::vector;
using std::stringstream;
using std::getline;
using std::cout;

// Sort class definition
class Sort
{
public:
	// default constructor with no parameters
	Sort();

	// Sort constructor with three parameters
	Sort(File_Management my_File_Management, const int numOfMapThreads, const int numOfReduceThreads);

	// Wrapper function to execute sort
	void runSort();

	// Wrapper function to execute sort master
	void runSortMaster();

	// member function to sort input vector of strings
	void sortInput();

	// member function to get the sorted output vector
	vector<string> getOutput();

	string extractAndPrepareString(string inputStringExtended, int inputCount);

	string decomposeAndBuildString(vector<string> inputStrings);

	void sortMaster();

private:
	// ** Helper Functions **
	
	// member function to extract just the word from the current line
	string getWord(string inputString);


	// ** Member Data **
	vector<string> input; // stores incoming vector to sort
	vector<string> output; // stores the new outgoing vector with elements in the reduced format
	File_Management currentSortFile; // stores local copy of file management object
	vector<string> debug; // stores a test vector of strings for debugging
	const int numOfInputFiles; // number of files to be sorted (equal to number of map threads)
	const int numOfOutputFiles; // number of files to be output (equal to number of files to be reduced)
};