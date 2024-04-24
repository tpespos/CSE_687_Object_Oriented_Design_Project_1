// Syracuse University
// CSE 687 Object Oriented Design

// Sort class function definitions. This file contains
// implementations of the member functions prototyped in Sort.h

#include "Sort.h"

// Sort default constructor
Sort::Sort()
	: count{ 0 }, element{ 0 }
{
	// empty body (add error message)
}

// Sort constructor with one parameter
Sort::Sort(File_Management fileManager)
	: count{ 0 }, element{ 0 }
{
	currentSortFile = fileManager; // copy file management obj to member data obj
	//debug = { "(\"act\",1)", "(\"i\",1)", "(\"counts\",1)", "(\"i\",1)" };
}

// Wrapper function to execute sort
void Sort::runSort() {
	input = currentSortFile.importSortFile(); // store input vector
	//input = debug; // ******** DEBUG *********
	sortInput();
	currentSortFile.exportSortFile(output);
}
/*
// member function to set input vector (not used with updates to File_Management)
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
	// string openQuote = "“";
	// string closeQuote = "”";
	string openQuote = "\"";
	string closeQuote = "\"";
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

	//std::cin.clear(); // clear buffer
	while (getline(ss, temp_str, '\"')) { // use double quotes as delimiter
		tokens.push_back(temp_str);
		//std::cin.clear(); // clear buffer
		//cout << temp_str; // ********** DEBUG ***********
	}

	return tokens[1]; // return second element of token vector (should be the word from source text)
};

//*/

string Sort::extractAndPrepareString(string inputStringExended, int inputCount) {

	int firstQuote = 0;
	int lastQuote = 0;
	firstQuote = inputStringExended.find_first_of("\"");
	lastQuote = inputStringExended.find_last_of("\"");

	//that is output string
	string word = inputStringExended.substr(firstQuote + 1, lastQuote - firstQuote - 1);

	string rowToAdd = "(\"" + word + "\", [1";
	for (int i = 1; i < inputCount; i++)	{
		rowToAdd += ", 1";
	}
	rowToAdd += "])";

	return rowToAdd;
}

// member function to sort input vector of strings
void Sort::sortInput() {
	
	sort(input.begin(), input.end());
	int numberOfWords = 0;
	for (int i = 0; i < input.size()-1; i++)	{
		numberOfWords++;
		if (input[i]!=input[i+1])		{
			output.push_back(extractAndPrepareString(input[i], numberOfWords));
			numberOfWords = 0;
		}
	}


	/*

	for (int i = 0; i < input.size(); i++) {
		//countReset();
		setCurrent();
		cout << count << "   " << current << "\n";
		bool check = checkIfCounted();
		if (check == false) {
			compare();
			output.push_back(getNewStr());
		}
		incrementElement();
	}
	//*/
};

// member function to get the sorted output vector
vector<string> Sort::getOutput() {
	return output;
};