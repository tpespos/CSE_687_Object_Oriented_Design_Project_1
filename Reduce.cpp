#include "Reduce.h"
#include "File_Management.h"


Reduce::Reduce() {
	//do nothing
}


Reduce::Reduce(File_Management files) {
	fileManagerUpdate(files);
}

int Reduce::fileManagerUpdate(File_Management newFileManeger) {
	fileManager = newFileManeger;
	inputFileName = fileManager.getFileBeingWorked();
	return 0;
}

int Reduce::reduceWrapper() {
	/*
	if (DEBUG==1)	{
		
		inputFileText.push_back("(“a”, [1, 1, 1])");
		inputFileText.push_back("(“the”, [1, 1, 1, 1, 1])");
		inputFileText.push_back("(“is”, [1, 1])");
	}
	else	{
		
	}
	//*/
	loadDataFromFile();

	//inputstring...get one line
	for (int i = 0; i < inputFileText.size(); i++)	{
		//intputstring into reduce
		string tempString;
		int tempCount;
		reduce(inputFileText[i],&tempString, &tempCount);

		//reduced line into output buffer
		exportFunction(tempString, tempCount);

		if (bufferToOutput.size() > 500000)		{
			//buffer to save
			writeBufferToSysAndClear();
		}
	}
	
	writeBufferToSysAndClear();
	//write success
	writeSuccessToFile();
	return 0;
}


int Reduce::reduce(string inputLine, string* outputString, int* outputCount) {
	
	//remove first bits
	//find first and last "
	int firstQuote = 0;
	int lastQuote = 0;
	firstQuote = inputLine.find_first_of("\"");
	lastQuote = inputLine.find_last_of("\"");

	//that is output string
	string word = inputLine.substr(firstQuote+1, lastQuote-firstQuote-1);


	//then count 1s in remainder
	int firstBracket = 0;
	int lastBracket = 0;
	firstBracket = inputLine.find_first_of("[");
	lastBracket = inputLine.find_last_of("]");
	string arrayOfNumbers = inputLine.substr(firstBracket + 1, lastBracket - firstBracket - 1);
	int count = 0;
	for (int i = 0; i < arrayOfNumbers.size(); i++)	{
		if (arrayOfNumbers.substr(i,1) == "1") {
			count++;
		}
	}
	//that is outputCount

	*outputString = word;
	*outputCount = count;
	return 0;
}

int Reduce::loadDataFromFile() {
	inputFileText = fileManager.importReduceFile();
	return 0;
}

int Reduce::exportFunction(string key, int reducedValue) {
	string rowToAdd = "(“" + key + "”,[" + to_string(reducedValue) + "])";	
	bufferToOutput.push_back(rowToAdd);
	return 0;
}

int Reduce::writeBufferToSysAndClear() {
	//use file IO to write buffer
	fileManager.exportReduceFile(bufferToOutput);

	bufferToOutput.clear();
	return 0;
}

int Reduce::writeSuccessToFile() {
	fileManager.outputSuccessFile();
	return 0;
}



/*
	string inputFileName;
	File_Management fileManager;
	vector<string> inputFileText;
	vector<string> bufferToOutput;
//*/
