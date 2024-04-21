#pragma once

// Include all of the built in libraries that will be used here
#include <vector>
#include <array>
#include <string>
#include <iostream>

#include "File_Management.h"
// Include all the functions that will be used from the STD namespace here
using std::string;
using std::vector;
using std::array;
//using std::cout;
//using std::endl;

//=====================================
//============= Map ===================
//=====================================

class Map_Tokenizer
{

public:

	Map_Tokenizer(File_Management inputFileObj)
	{
		fileObj = inputFileObj;
		//fileName = inputFileObj.getFileBeingWorked();
		//lineToBeParsed = lineOftextToBeParsed;
	}

	void map(string fileName, string lineToBeParsed)
	{

	}

	void export(string word, string value)
	{

	}


	void this_is_DUMB();

private:

	File_Management fileObj;
	string fileName;
};

