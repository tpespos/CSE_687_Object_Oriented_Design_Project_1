

#pragma once
#include <string>
using namespace std;


class Reduce
{
	//constructor

	//destructor

public:
	//methods
	int reduce(string inputLine, string *outputLine);
	int exportFunction(string key, int reducedValue);
	void loadDataFromFile(string inputFileName);

	int writeSuccessToFile();


private:
	//vars

	string inputFileName;
	string inputFileText;


};

