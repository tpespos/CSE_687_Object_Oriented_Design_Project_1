#pragma once

#include "File_Management.h"

#include <vector>
#include <string>

using std::string;
using std::vector;

class Map_Tokenizer
{

public:

	Map_Tokenizer(File_Management inputFileObj);

	void mapDLL(string dllPathandName, string fileName, string lineToBeParsed);

	//void writeTofile();

private:

	File_Management fileObj;
	
	/*vector<string> wordBuffer;
	vector<int> valueBuffer;

	void removeNonLetterCharacters(string& inputString);

	void blankNonLetterCharacters(string& inputString);

	void changeAllUpperCaseToLowerCase(string& inputString);

	vector<string> buildTempMapVector(vector<string> tokens);

	void exportMap(string word, int value);*/

};

