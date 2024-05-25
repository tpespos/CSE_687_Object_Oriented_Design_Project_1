#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "File_Management.h"
using namespace std;

#ifdef DLL_EXPORT
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

//extern "C" {
		//methods
		int reduceWrapper(File_Management fileManager, string partNum, bool isMasterReducer);
		//vector<string> loadDataFromFile(File_Management fileManager);
		int reduce(string inputLine, string* outputString, int* outputCount);
		int exportFunction(string key, int reducedValue, vector<string>*);
//}