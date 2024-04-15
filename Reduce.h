

#pragma once
#include <string>
#using std::namespace;


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

