#include "pch.h"
#include "ReduceDLL.h"


#include "File_Management.h"

int reduceWrapper(File_Management fileManager) {
	cout << "entering wrapper\n";
	//File_Management fileManager;
	vector<string> inputFileText = loadDataFromFile(fileManager);
	vector<string> bufferToOutput;
	//inputstring...get one line
	for (int i = 0; i < inputFileText.size(); i++) {
		//intputstring into reduce
		string tempString;
		int tempCount;
		//cout << "inputing files\n";
		//cout << "reducing\n";
		reduce(inputFileText[i], &tempString, &tempCount);
		//cout << "inputline: "<<tempString << "\n";
		//reduced line into output buffer
		//cout << "exporting\n";
		exportFunction(tempString, tempCount, &bufferToOutput);
		if (bufferToOutput.size() > 5000) {
			//buffer to save
			cout << "exportingfiles\n";
			fileManager.exportReduceFile(bufferToOutput);
			bufferToOutput.clear();
		}
	}
	cout << "wrting to final buffer\n";
	fileManager.exportReduceFile(bufferToOutput);
	bufferToOutput.clear();

	//write success
	fileManager.outputSuccessFile();

	return 0;
}

int reduce(string inputLine, string* outputString, int* outputCount) {

	//remove first bits
	//find first and last "
	int firstQuote = 0;
	int lastQuote = 0;
	firstQuote = inputLine.find_first_of("\"");
	lastQuote = inputLine.find_last_of("\"");

	//that is output string
	string word = inputLine.substr(firstQuote + 1, lastQuote - firstQuote - 1);


	//then count 1s in remainder
	int firstBracket = 0;
	int lastBracket = 0;
	firstBracket = inputLine.find_first_of("[");
	lastBracket = inputLine.find_last_of("]");
	string arrayOfNumbers = inputLine.substr(firstBracket + 1, lastBracket - firstBracket - 1);
	int count = 0;
	for (int i = 0; i < arrayOfNumbers.size(); i++) {
		if (arrayOfNumbers.substr(i, 1) == "1") {
			count++;
		}
	}
	//that is outputCount

	*outputString = word;
	*outputCount = count;
	return 0;
}

vector<string> loadDataFromFile(File_Management fileManager) {
	vector<string> inputFileText = fileManager.importReduceFile();
	return inputFileText;
}

int exportFunction(string key, int reducedValue, vector<string> *bufferToOutput) {
	string rowToAdd = "(“" + key + "”,[" + to_string(reducedValue) + "])";
	bufferToOutput->push_back(rowToAdd);
	return 0;
}

