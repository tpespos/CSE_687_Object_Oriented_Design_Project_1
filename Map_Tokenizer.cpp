#include "Map_Tokenizer.h"

#include "framework.h"
#include <iostream>
#include <sstream>

Map_Tokenizer::Map_Tokenizer(File_Management inputFileObj)
{
	fileObj = inputFileObj;
}

int Map_Tokenizer::runMap(string dllPathandName, string interFilePath, vector<string> fileParsedLineVector, int threadNumber)
{
	vector<string> output;
	vector<string> combined_output_1;
	vector<string> combined_output_2;
	vector<string> combined_output_3;
	/*
	string interFilePathWithoutTXTatEnd = interFilePath.erase(interFilePath.size() - 4);
	string interFilePathForCombinedOutput1 = interFilePathWithoutTXTatEnd;
	string interFilePathForCombinedOutput2 = interFilePathWithoutTXTatEnd;
	string interFilePathForCombinedOutput3 = interFilePathWithoutTXTatEnd;
	interFilePathForCombinedOutput1.append("_1.txt");
	interFilePathForCombinedOutput2.append("_2.txt");
	interFilePathForCombinedOutput3.append("_3.txt");
	*/
	int bufferToBeFilled = 1;

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

				if (bufferToBeFilled == 1)
				{
					combined_output_1.insert(combined_output_1.end(), output.begin(), output.end());
					bufferToBeFilled = 2;
				}
				else if (bufferToBeFilled == 2)
				{
					combined_output_2.insert(combined_output_2.end(), output.begin(), output.end());
					bufferToBeFilled = 3;
				}
				else if (bufferToBeFilled == 3)
				{
					combined_output_3.insert(combined_output_3.end(), output.begin(), output.end());
					bufferToBeFilled = 1;
				}
				
			}
			//mapFun(interFilePath, "END_OF_FILE_FLUSH_BUFFER");
			//fileObj.exportMapFile(interFilePathForCombinedOutput1, combined_output_1);
			//fileObj.exportMapFile(interFilePathForCombinedOutput2, combined_output_2);
			//fileObj.exportMapFile(interFilePathForCombinedOutput3, combined_output_3); 
			fileObj.exportMapFile(to_string(threadNumber+1), "1", combined_output_1);
			fileObj.exportMapFile(to_string(threadNumber+1), "2", combined_output_2);
			fileObj.exportMapFile(to_string(threadNumber+1), "3", combined_output_3);
		}

		// Free the DLL
		FreeLibrary(hDLL);
	}


	return 0;
}
