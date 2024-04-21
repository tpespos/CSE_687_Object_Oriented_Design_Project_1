#include "Reduce.h"



Reduce::Reduce(File_Management files) {

}

int Reduce::fileManagerUpdate(File_Management newFileManeger) {
	fileManager = newFileManeger;
	inputFileName = fileManager.getIntermediateFiles()[0];
	return 1;
}

int Reduce::reduceWrapper() {
	
	if (DEBUG==1)	{
		
		inputFileText.push_back("(“a”, [1, 1, 1])");
		inputFileText.push_back("(“the”, [1, 1, 1, 1, 1])");
		inputFileText.push_back("(“is”, [1, 1])");
	}
	else	{
		loadDataFromFile(inputFileName);
	}
	
	//inputstring...get one line
	for (int i = 0; i < inputFileText.size(); i++)	{
		//intputstring into reduce
		string tempString;
		int tempCount;
		reduce(inputFileText[i],&tempString, &tempCount);

		//reduced line into output buffer
		exportFunction(tempString, tempCount);

		if (bufferToOutput.size() > 5000)		{
			//buffer to save
			writeSuccessToFile();
		}
	}
	//write success
	writeSuccessToFile();
	return 0;
}


int Reduce::reduce(string inputLine, string* outputString, int* outputCount) {
	
	//remove first bits
	//find first and last "
	int firstQuote = 0;
	int lastQuote = 0;
	firstQuote = inputLine.find_first_of("""");
	lastQuote = inputLine.find_last_of("""");

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

int Reduce::loadDataFromFile(string inputFileName) {
	//???? what to write vs tommys code
	return 0;
}

int Reduce::exportFunction(string key, int reducedValue) {
	string rowToAdd = "(""" + key + """,[" + to_string(reducedValue) + "])";	
	bufferToOutput.push_back(rowToAdd);
	return 0;
}

int Reduce::writeBufferToSysAndClear() {
	//use file IO to write buffer

	bufferToOutput.clear();
	return 0;
}

int Reduce::writeSuccessToFile() {
	//write "success.txt" as a file using file class
	return 0;
}



/*
	string inputFileName;
	File_Management fileManager;
	vector<string> inputFileText;
	vector<string> bufferToOutput;
//*/
