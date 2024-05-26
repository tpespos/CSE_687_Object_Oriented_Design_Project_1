// Syracuse University
// CSE 687 Object Oriented Design

// Sort class function definitions. This file contains
// implementations of the member functions prototyped in Sort.h

#include "Sort.h"

// overload ostream operator to print vector for debugging purposes
template <typename S>
ostream& operator<<(ostream& os, const vector<S>& vector)
{
	// Printing all the elements
	// using <<
	for (auto element : vector) {
		os << element << " ";
	}
	return os;
}

// Sort default constructor
Sort::Sort()
	: numOfInputFiles{ 0 }, numOfOutputFiles{ 0 }
{
	// empty body (add error message)
}

// Sort constructor with three parameters
Sort::Sort(File_Management fileManager, const int numOfMapThreads, const int numOfReduceThreads)
	: numOfInputFiles{numOfMapThreads}, numOfOutputFiles{numOfReduceThreads}
{
	currentSortFile = fileManager; // copy file management obj to member data obj
	//debug = { "(\"act\",1)", "(\"i\",1)", "(\"counts\",1)", "(\"i\",1)" };
}

// Wrapper function to execute sort
void Sort::runSort() {
	vector<string> temp;
	string fileNumber;
	string partNumber;
	bool isThisTheMasterSortFunction = FALSE;

	// loop to create required number of reduce files
	for (int i = 1; i <= numOfOutputFiles; i++) {
		partNumber = to_string(i);

		// loop through all incoming MAP files
		for (int j = 1; j <= numOfInputFiles; j++) {
			fileNumber = to_string(j);
			temp = currentSortFile.importSortFile(fileNumber, partNumber, isThisTheMasterSortFunction);
			input.insert(input.end(), temp.begin(), temp.end()); // insert temp vector at end of input
			temp.clear();
		}

		sortInput();
		currentSortFile.exportSortFile(partNumber, output, isThisTheMasterSortFunction);

		// clear buffers before moving to next set of files
		output.clear();
		input.clear();
	}
}

// Wrapper function to execute sort master
void Sort::runSortMaster() {
	vector<string> temp;
	string fileNumber = to_string(1); // only partNumber is required to change for sort master
	string partNumber;
	bool isThisTheMasterSortFunction = TRUE;

	// loop to create a single sorted output file (Smaster)
	for (int i = 1; i <= numOfOutputFiles; i++) {
		partNumber = to_string(i);
		temp = currentSortFile.importSortFile(fileNumber, partNumber, isThisTheMasterSortFunction);
		input.insert(input.end(), temp.begin(), temp.end()); // insert temp vector at end of input
		temp.clear();
	}

	sortMaster();
	currentSortFile.exportSortFile(partNumber, output, isThisTheMasterSortFunction);

	// clear buffers
	output.clear();
	input.clear();
}

string Sort::extractAndPrepareString(string inputStringExtended, int inputCount) {
	string rowToAdd = "(\"" + getWord(inputStringExtended) + "\", [1";
	for (int i = 1; i < inputCount; i++)	{
		rowToAdd += ", 1";
	}
	rowToAdd += "])";

	return rowToAdd;
}

// Sort master version of extractAndPrepareString
string Sort::decomposeAndBuildString(vector<string> inputStrings) {
	// local variables
	string arrayOfNumbers;

	// decompose each string and store pieces in local variables
	for (int i = 0; i < inputStrings.size(); i++) {
		int firstBracket = 0;
		int lastBracket = 0;
		firstBracket = inputStrings[i].find_first_of("[");
		lastBracket = inputStrings[i].find_first_of("]");
		arrayOfNumbers.append(inputStrings[i].substr(firstBracket + 1, lastBracket - firstBracket - 1));

		// only append a comma if it is not the last string in the vector
		if (i + 1 < inputStrings.size()) {
			arrayOfNumbers.append(", ");
		}
	}

	// build output string
	string rowToAdd = "(\"" + getWord(inputStrings[0]) + "\", " + "[" + arrayOfNumbers + "])";
	return rowToAdd;
}

// Sort master
void Sort::sortMaster() {
	vector<string> extracted; // holds subset of strings of the same word to be sorted

	sort(input.begin(), input.end());

	for (int i = 0; i < input.size() - 1; i++) {

		extracted.push_back(input[i]);
		string currentWord = getWord(input[i]);
		string nextWord = getWord(input[i + 1]);

		if (currentWord != nextWord) {
			output.push_back(decomposeAndBuildString(extracted));
			extracted.clear(); // clear buffer

			// check to make sure last element of input vector is accounted for
			if (i + 1 == input.size() - 1) {
				extracted.push_back(input[i + 1]);
				output.push_back(decomposeAndBuildString(extracted));
			}
		}
	}
}

// member function to sort input vector of strings
void Sort::sortInput() {
	
	sort(input.begin(), input.end());
	int numberOfWords = 0;
	for (int i = 0; i < input.size() - 1; i++)	{
		numberOfWords++;
		if (input[i] != input[i + 1])		{
			output.push_back(extractAndPrepareString(input[i], numberOfWords));
			numberOfWords = 0;
			
			// check to make sure last element of input vector is accounted for
			if (i + 1 == input.size() - 1) {
				output.push_back(extractAndPrepareString(input[i + 1], 1));
			}
		}
	}
};

// member function to extract just the word from the current line
string Sort::getWord(string inputString) {
	int firstQuote = 0;
	int lastQuote = 0;
	firstQuote = inputString.find_first_of("\"");
	lastQuote = inputString.find_last_of("\"");
	string word = inputString.substr(firstQuote + 1, lastQuote - firstQuote - 1);
	return word;
}

// member function to get the sorted output vector
vector<string> Sort::getOutput() {
	return output;
};