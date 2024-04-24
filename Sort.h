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

	// Sort constructor with one parameter
	Sort(File_Management my_File_Management);

	// Wrapper function to execute sort
	void runSort();

	// member function to sort input vector of strings
	void sortInput();

	// member function to get the sorted output vector
	vector<string> getOutput();

private:
	// ** Helper Functions **
	// set input vector
	void setInput(vector<string> inc);

	// increase the value of count by 1
	void countUp();

	// reset the value of count to zero
	void countReset();

	// increase the value of element by 1
	void incrementElement();

	// store the current element of the input vector
	void setCurrent();

	// count the number of times word appears in the input vector
	void compare();

	// check if the current word is already in the output vector
	bool checkIfCounted();

	// create reduced element
	string getNewStr();

	// return token from current element of the input vector
	string tokenize(string original);

	// ** Member Data **
	int count; // stores the number of times a word appears in a vector
	int element; // stores the element number of the input vector currently being used
	string current; // stores the current string from the input vector
	vector<string> input; // stores incoming vector to sort
	vector<string> output; // stores the new outgoing vector with elements in the reduced format
	File_Management currentSortFile; // stores local copy of file management object
	vector<string> debug; // stores a test vector of strings for debugging
};