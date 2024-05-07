#include "Map_Tokenizer.h"

#include "framework.h"
#include <iostream>
#include <sstream>

Map_Tokenizer::Map_Tokenizer(File_Management inputFileObj)
{
	fileObj = inputFileObj;
}

int Map_Tokenizer::runMap(string dllPathandName, string interFilePath, vector<string> fileParsedLineVector)
{
	typedef void (*MapDllFunc)(string, string);
	// Load the DLL dynamically
	std::wstring stemp = std::wstring(dllPathandName.begin(), dllPathandName.end());
	LPCWSTR dllPN = stemp.c_str();
	HINSTANCE hDLL = LoadLibrary(dllPN);
	if (hDLL != NULL)
	{
		// Get pointer to the map function
		MapDllFunc mapFun = (MapDllFunc)GetProcAddress(hDLL, "map");
		if (mapFun != NULL)
		{
			// Iterate over all the lines of a single file
			for (int i = 0; i < fileParsedLineVector.size(); i++)
			{
				mapFun(interFilePath, fileParsedLineVector[i]);
			}
			mapFun(interFilePath, "END_OF_FILE_FLUSH_BUFFER");
		}
	}
	// Free the DLL
	FreeLibrary(hDLL);

	return 0;
}
