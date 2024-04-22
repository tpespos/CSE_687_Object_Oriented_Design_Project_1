// Syracuse University
// CSE 687 Object Oriented Design

// Sort class function definitions. This file contains
// implementations of the member functions prototyped in Sort.h

#include "Sort.h"

// Sort default constructor
Sort::Sort()
	: count{ 0 }, element{ 0 }
{
	// add error message
}

// Sort constructor with one parameter
Sort::Sort(File_Management fileManager)
	: count{ 0 }, element{ 0 }
{
	Sort::setInput(fileManager.importSortFile()); // store input vector
	Sort::sortInput();	// store first element of input vector
	fileManager.exportSortFile(Sort::getOutput()); // export the sorted intermediate file
}

// member function to set input vector
void Sort::setInput(vector<string> inc) {
	input = inc;
};

// member function to increase the value of count by 1
void Sort::countUp() {
	count++;
};

// member function to reset the value of count to zero
void Sort::countReset() {
	count = 0;
};

// member funciton to increase the value of element by 1
void Sort::incrementElement() {
	element++;
};

// member function to store the current element of the input vector
void Sort::setCurrent() {
	current = input[element];
};

// member function to count the number of times word appears in the input vector
void Sort::compare() {
	string word = tokenize(current); // get current word from input string

	for (int i = 0; i < input.size(); i++) {
		string temp = tokenize(input[i]); // get word to compare from input vector
		if (word == temp) {
			countUp(); // increase count
		}
	}
};

// member function to check if the current word is already in the output vector
bool Sort::checkIfCounted() {
	string word = tokenize(current); // get current word from input string

	for (int i = 0; i < output.size(); i++) {
		string temp = tokenize(output[i]); // get word to compare from input vector
		if (word == temp) {
			return true;
		}
	}
	return false;
};

// member function to create reduced element
string Sort::getNewStr() {
	string openPar = "(";
	string closePar = ")";
	string openQuote = "“";
	string closeQuote = "”";
	string comma = ",";
	string leftBrack = "[1";
	string rightBrack = "]";
	string key = ", 1";
	string temp;

	// loop to add the correct amount of keys
	for (int i = 0; i < count; i++) {
		temp = temp + key;
	}

	// assemble new string in reduced format
	string new_str = openPar + openQuote + tokenize(current) + closeQuote + comma + leftBrack + temp + rightBrack + closePar;
	return new_str;
};

// member function to return token from current element of the input vector
string Sort::tokenize(string original) {
	stringstream ss(original); // convert current string into string stream
	vector<string> tokens;
	string temp_str;

	while (getline(ss, temp_str, '\"')) { // use double quotes as delimiter
		tokens.push_back(temp_str);
	}
	return tokens[1]; // return second element of token vector (should be the word from source text)
};

// member function to sort input vector of strings
void Sort::sortInput() {
	for (int i = 0; i < input.size(); i++) {
		countReset();
		setCurrent();
		bool check = checkIfCounted();
		if (check == false) {
			compare();
			output.push_back(getNewStr());
		}
		incrementElement();
	}
};

// member function to get the sorted output vector
vector<string> Sort::getOutput() {
	return output;
};