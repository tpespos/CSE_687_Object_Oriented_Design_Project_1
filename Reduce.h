

#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "File_Management.h"
using namespace std;


class Reduce
{
	//constructor
	Reduce(File_Management files);

	//destructor

public:
	//methods
	int reduceWrapper();
	int loadDataFromFile(string inputFileName);
	int reduce(string inputLine, string* outputString, int* outputCount);
	int exportFunction(string key, int reducedValue);
	int writeBufferToSysAndClear();
	int writeSuccessToFile();

	int fileManagerUpdate(File_Management newFileManeger);


private:
	//vars

	string inputFileName;
	File_Management fileManager;
	vector<string> inputFileText;
	vector<string> bufferToOutput;

	int DEBUG;
	

};

