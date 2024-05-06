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

private:

	File_Management fileObj;
	
};

