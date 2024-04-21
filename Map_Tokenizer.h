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
#include <sstream>
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

		stringstream ss(lineToBeParsed); //convert lineToBeParsed into string stream
		vector<string> tokens;
		string temp_str;

		while (getline(ss, temp_str, ' ')) { //use comma as delim for cutting string
			removeNonLetterCharacters(temp_str);
			tokens.push_back(temp_str);
		}

		for (int i = 0; i < tokens.size(); i++) {
			cout << tokens[i] << endl;
		}

	}

	

	/*void export(string word, string value)
	{

	}*/


	void this_is_DUMB();

private:

	File_Management fileObj;
	string fileName;

	void removeNonLetterCharacters(string &inputString)
	{
		for (int i = 0; i < inputString.size(); i++) {
			if (inputString[i] < 'A' || inputString[i] > 'Z' &&
				inputString[i] < 'a' || inputString[i] > 'z')
			{
				inputString.erase(i, 1);
				i--;
			}
		}
	}

};

