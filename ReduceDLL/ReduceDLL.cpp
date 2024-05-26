#include "pch.h"
#include "ReduceDLL.h"

#include "File_Management.h"

int reduceWrapper(File_Management fileManager, string partNum, bool isMasterReducer) {
	//cout << "entering wrapper\n";
	//File_Management fileManager;
	//cout << "path1: " << fileManager.importReduceFile()[0];

	//vector<string> File_Management::importReduceFile(string partNumber, bool thisIsTheFinalOutputFile)

	//cout << "importing...PN:"<< partNum<< "\n";
	vector<string> inputFileText = fileManager.importReduceFile(partNum, isMasterReducer);
		//loadDataFromFile(fileManager);

	//cout << "imported\n";
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
			//cout << "exportingfiles\n";

			//void File_Management::exportReduceFile(string partNumber, const vector<string>& data, bool thisIsTheFinalOutputFile)
			//cout << "export...PN:" << partNum << "\n";
			fileManager.exportReduceFile(partNum, bufferToOutput, isMasterReducer);
			bufferToOutput.clear();
		}
	}
	//cout << "wrting to final buffer\n";
	//cout << "export...PN:" << partNum << "\n";
	fileManager.exportReduceFile(partNum, bufferToOutput, isMasterReducer);
	bufferToOutput.clear();

	//write success
	if (isMasterReducer)
	{
		//cout << "success...PN:" << partNum << "\n";
		fileManager.outputSuccessFile();
	}
	

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

	//cout << "entering counting\n";

	//then sum remainder
	int firstBracket = 0;
	int lastBracket = 0;
	firstBracket = inputLine.find_first_of("[");
	lastBracket = inputLine.find_last_of("]");
	string arrayOfNumbers = inputLine.substr(firstBracket + 1, lastBracket - firstBracket - 1);
	arrayOfNumbers.append(",");
	int count = 0;
	while (arrayOfNumbers.length() > 0) {
		
		//find next,
		int nextCommaLoc = arrayOfNumbers.find(",");
		//find number
		
		string numberToAddString = arrayOfNumbers.substr(0, nextCommaLoc);
		//cout <<  "num string : " << numberToAddString << "\n";
		//convert number to int
		//add int
		count += stoi(numberToAddString);
		//remove current number from string
		arrayOfNumbers = arrayOfNumbers.substr(nextCommaLoc+1, arrayOfNumbers.length());
		//repeat
		//cout << "num string:" << numberToAddString << "  num int:" << stoi(numberToAddString) << "  count:" << count << "  str remain length:" << arrayOfNumbers.length() << "  str remain:" << arrayOfNumbers << "\n";
		
	}

	//for (int i = 0; i < arrayOfNumbers.size(); i++) {
	//	if (arrayOfNumbers.substr(i, 1) == "1") {
	//		count++;
	//	}
	//}
	//that is outputCount

	*outputString = word;
	*outputCount = count;
	return 0;
}


int exportFunction(string key, int reducedValue, vector<string> *bufferToOutput) {
	string rowToAdd = "(\"" + key + "\",[" + to_string(reducedValue) + "])";
	bufferToOutput->push_back(rowToAdd);
	return 0;
}

