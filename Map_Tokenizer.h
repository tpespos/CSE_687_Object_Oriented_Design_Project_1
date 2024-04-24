#pragma once

#include <vector>
#include <array>
#include <string>
#include <iostream>
#include <sstream>

#include "File_Management.h"

using std::string;
using std::vector;
using std::array;

class Map_Tokenizer
{

public:

	Map_Tokenizer(File_Management inputFileObj);

	void map(string fileName, string lineToBeParsed);

private:

	File_Management fileObj;

	void removeNonLetterCharacters(string& inputString);

	void changeAllUpperCaseToLowerCase(string& inputString);

	vector<string> buildTempMapVector(vector<string> tokens);

};

