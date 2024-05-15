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
	vector<string> output;
	vector<string> combined_output;
	typedef vector<string> (*MapDllFunc)(string, string);
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
				if (fileParsedLineVector[i].empty())
				{
					continue;
				}
				output = mapFun(interFilePath, fileParsedLineVector[i]);
				combined_output.insert(combined_output.end(), output.begin(), output.end());
			}
			//mapFun(interFilePath, "END_OF_FILE_FLUSH_BUFFER");
			fileObj.exportMapFile(interFilePath, combined_output);
		}
	}
	// Free the DLL
	FreeLibrary(hDLL);

	return 0;
}
