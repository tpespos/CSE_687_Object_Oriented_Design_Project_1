#pragma once

// Syracuse University
// CSE 687 Object Oriented Design

#include <iostream> // debug purposes
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
	Sort(vector<string> input_vec);

	// member function to sort input vector of strings
	void sortInput();

	// member function to get the sorted output vector
	vector<string> getOutput();

private:
	// member function to set input vector
	void setInput(vector<string> inc);

	// member function to increase the value of count by 1
	void countUp();

	// member function to reset the value of count to zero
	void countReset();

	// member function to increase the value of element by 1
	void incrementElement();

	// member function to store the current element of the input vector
	void setCurrent();

	// member function to count the number of times word appears in the input vector
	void compare();

	// member function to check if the current word is already in the output vector
	bool checkIfCounted();

	// member function to create reduced element
	string getNewStr();

	// member function to return token from current element of the input vector
	string tokenize(string original);

	// Member Data
	int count; // stores the number of times a word appears in a vector
	int element; // stores the element number of the input vector currently being used
	string current; // stores the current string from the input vector
	vector<string> input; // stores incoming vector to sort
	vector<string> output; // stores the new outgoing vector with elements in the reduced format 
};