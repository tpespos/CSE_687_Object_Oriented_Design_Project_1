#include "Map_Tokenizer.h"

#include "framework.h"
//#include <windows.h>
#include <iostream>
#include <sstream>

//using namespace std;

Map_Tokenizer::Map_Tokenizer(File_Management inputFileObj)
{
	fileObj = inputFileObj;
}

void Map_Tokenizer::mapDLL(string dllPathandName, string fileName, string lineToBeParsed)
{
    // Declare the function prototype manually
    typedef void (*AddFunc)(string, string);

    // Load the DLL dynamically

    std::wstring stemp = std::wstring(dllPathandName.begin(), dllPathandName.end());
    LPCWSTR dllPN = stemp.c_str();

    //HINSTANCE hDLL = LoadLibrary(TEXT("C:\\Users\\lodin\\Documents\\College_work\\Spring2024\\OOD_Wensday_Class\\Project1\\code\\x64\\Debug\\mapDLL.dll"));

    HINSTANCE hDLL = LoadLibrary(dllPN);
    if (hDLL != NULL) {
        // Get pointer to the map function
        AddFunc mapFun = (AddFunc)GetProcAddress(hDLL, "map");
        if (mapFun != NULL) {
            // Call the map function
            mapFun(fileName, lineToBeParsed);
        }
        else {
            std::cerr << "Failed to get function pointer." << std::endl;
            cout << GetLastError();
        }
        // Free the DLL
        FreeLibrary(hDLL);
    }
    else {
        std::cerr << "Failed to load DLL." << std::endl;
    }

}

//void Map_Tokenizer::removeNonLetterCharacters(string& inputString)
//{
//	for (int i = 0; i < inputString.size(); i++) {
//		if ((inputString[i] < 'A' || inputString[i] > 'Z' &&
//			inputString[i] < 'a' || inputString[i] > 'z'))
//		{
//			inputString.erase(i, 1);
//			i--;
//		}
//	}
//}
//
//void Map_Tokenizer::blankNonLetterCharacters(string& inputString)
//{
//	for (int i = 0; i < inputString.size(); i++) {
//		if ((inputString[i] < 'A' || inputString[i] > 'Z' &&
//			inputString[i] < 'a' || inputString[i] > 'z'))
//		{
//			inputString[i] = ' ';
//		}
//	}
//}
//
//void Map_Tokenizer::changeAllUpperCaseToLowerCase(string& inputString)
//{
//	for (int i = 0; i < inputString.size(); i++) {
//		if (inputString[i] >= 'A' && inputString[i] <= 'Z')
//		{
//			inputString[i] = inputString[i] + 32;
//		}
//	}
//
//}
//
//vector<string> Map_Tokenizer::buildTempMapVector(vector<string> tokens)
//{
//	vector<string> output;
//	string openPar = "(";
//	string closePar = ")";
//	string quote = "\"";
//	string comma = ",";
//
//	sort(tokens.begin(), tokens.end());
//
//	for (int i = 0; i < tokens.size(); i++)
//	{
//		string temp = openPar + quote + tokens[i] + quote +
//			comma + "1" + closePar;
//
//		output.push_back(temp);
//		//i = i + count - 1;
//	}
//	return output;
//}
//
//void Map_Tokenizer::exportMap(string word, int value)
//{
//	wordBuffer.push_back(word);
//	valueBuffer.push_back(value);
//}
//
//void Map_Tokenizer::writeTofile()
//{
//	vector<string> outputVector = buildTempMapVector(wordBuffer);
//	fileObj.exportMapFile(outputVector);
//	wordBuffer.clear();
//	valueBuffer.clear();
//}

