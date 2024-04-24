#include "Map_Tokenizer.h"


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

	while (getline(ss, temp_str, ' ')) { //use comma as delim for cutting string
		if (temp_str.empty()) continue;
		removeNonLetterCharacters(temp_str);
		changeAllUpperCaseToLowerCase(temp_str);
		tokens.push_back(temp_str);
	}

	/*for (int i = 0; i < tokens.size(); i++) {
		cout << tokens[i] << endl;
	}*/

	vector<string> outputVector = buildTempMapVector(tokens);

	/*for (int i = 0; i < outputVector.size(); i++) {
		cout << outputVector[i] << endl;
	}*/

	fileObj.exportMapFile(outputVector);

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