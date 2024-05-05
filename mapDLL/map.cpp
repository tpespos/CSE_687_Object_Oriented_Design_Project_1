
#include "pch.h"

#include "File_Management_map.h"
#include "map.h"
#include <iostream>
#include <sstream>
#include <algorithm>
using std::stringstream;

void map(string fileName, string lineToBeParsed)
{

	// Force blanks on non-alpha chars
	blankNonLetterCharacters(lineToBeParsed);

	stringstream ss(lineToBeParsed); //convert lineToBeParsed into string stream
	vector<string> tokens;
	string temp_str;
	vector<int> count;

	while (getline(ss, temp_str, ' ')) { //use comma as delim for cutting string
		if (temp_str.empty()) continue;
		removeNonLetterCharacters(temp_str);
		changeAllUpperCaseToLowerCase(temp_str);
		if (!temp_str.empty())
		{
			exportMap(fileName,temp_str, 1);
		}
	}
	exportMap(fileName, temp_str, -1);
}

void removeNonLetterCharacters(string& inputString)
{
	for (int i = 0; i < inputString.size(); i++) {
		if ((inputString[i] < 'A' || inputString[i] > 'Z' &&
			inputString[i] < 'a' || inputString[i] > 'z'))
		{
			inputString.erase(i, 1);
			i--;
		}
	}
}

void changeAllUpperCaseToLowerCase(string& inputString)
{
	for (int i = 0; i < inputString.size(); i++) {
		if (inputString[i] >= 'A' && inputString[i] <= 'Z')
		{
			inputString[i] = inputString[i] + 32;
		}
	}

}

void blankNonLetterCharacters(string& inputString)
{
	for (int i = 0; i < inputString.size(); i++) {
		if ((inputString[i] < 'A' || inputString[i] > 'Z' &&
			inputString[i] < 'a' || inputString[i] > 'z'))
		{
			inputString[i] = ' ';
		}
	}
}

vector<string> buildTempMapVector(vector<string> tokens)
{
	vector<string> output;
	string openPar = "(";
	string closePar = ")";
	string quote = "\"";
	string comma = ",";

	sort(tokens.begin(), tokens.end());

	for (int i = 0; i < tokens.size(); i++)
	{
		string temp = openPar + quote + tokens[i] + quote +
			comma + "1" + closePar;

		output.push_back(temp);
		//i = i + count - 1;
	}
	return output;
}

void exportMap(string filename, string word, int value)
{
	static vector<string> wordBuffer;
	static vector<int>    valueBuffer;

	if (value != -1)
	{
		wordBuffer.push_back(word);
		valueBuffer.push_back(value);
	}
	if ((value == -1) || (wordBuffer.size() > 10000))
	{
		// Write to file
		vector<string> wordBufferOut = wordBuffer;
		vector<int>    valueBufferOut = valueBuffer;
		writeTofile(filename, wordBufferOut, valueBufferOut);
		wordBuffer.clear();
		valueBuffer.clear();
	}
}

void writeTofile(string fileName, vector<string> wordBuffer, vector<int> valueBuffer)
{
	vector<string> outputVector = buildTempMapVector(wordBuffer);
	File_Management::exportMapFile(fileName, outputVector);
}