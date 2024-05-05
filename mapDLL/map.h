#pragma once

#ifdef DLL_EXPORT
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

#include <string>
#include <vector>

using std::string;
using std::vector;


void DLL_API map(string fileName, string lineToBeParsed);

void removeNonLetterCharacters(string& inputString);

void changeAllUpperCaseToLowerCase(string& inputString);

void blankNonLetterCharacters(string& inputString);

vector<string> buildTempMapVector(vector<string> tokens);

void exportMap(string filename, string word, int value);

void writeTofile(string fileName, vector<string> wordBuffer, vector<int> valueBuffer);
