#include "Map_Tokenizer.h"

#include <iostream>
#include <sstream>

Map_Tokenizer::Map_Tokenizer(File_Management inputFileObj)
{
	fileObj = inputFileObj;
}

void Map_Tokenizer::map(string fileName, string lineToBeParsed)
{

	stringstream ss(lineToBeParsed); //convert lineToBeParsed into string stream
	vector<string> tokens;
	string temp_str;
	vector<int> count;
	wordBuffer.clear();
	valueBuffer.clear();

	if (lineToBeParsed.length() > 0)
	{
		while (getline(ss, temp_str, ' ')) { //use comma as delim for cutting string
			if (temp_str.empty()) continue;
			removeNonLetterCharacters(temp_str);
			changeAllUpperCaseToLowerCase(temp_str);
			exportMap(temp_str, 1);
		}
		writeTofile();
	}
}
void Map_Tokenizer::removeNonLetterCharacters(string& inputString)
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

void Map_Tokenizer::changeAllUpperCaseToLowerCase(string& inputString)
{
	for (int i = 0; i < inputString.size(); i++) {
		if (inputString[i] >= 'A' && inputString[i] <= 'Z')
		{
			inputString[i] = inputString[i] + 32;
		}
	}

}

vector<string> Map_Tokenizer::buildTempMapVector(vector<string> tokens)
{
	vector<string> output;
	string openPar = "(";
	string closePar = ")";
	string quote = "\"";
	string comma = ",";

	sort(tokens.begin(), tokens.end());

	for (int i = 0; i < tokens.size(); i++)
	{
		int count = 0;
		while (((i + count) < tokens.size()) && (tokens[i] == tokens[i + count]))
		{
			count++;
		}
		//string temp = openPar + quote + tokens[i] + quote +
		//			  comma + to_string(count) + closePar;

		string temp = openPar + quote + tokens[i] + quote +
			comma + "1" + closePar;

		output.push_back(temp);
		i = i + count - 1;
	}
	return output;
}

void Map_Tokenizer::exportMap(string word, int value)
{
	wordBuffer.push_back(word);
	valueBuffer.push_back(value);
}

void Map_Tokenizer::writeTofile()
{
	vector<string> outputVector = buildTempMapVector(wordBuffer);
	fileObj.exportMapFile(outputVector);
}

