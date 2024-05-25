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

	int runMap(string dllPathandName, string interFilePath, vector<string> fileParsedLineVector, int threadNumber);

private:

	File_Management fileObj;
	
};

