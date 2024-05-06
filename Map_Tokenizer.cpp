#include "Map_Tokenizer.h"

#include "framework.h"
#include <iostream>
#include <sstream>

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
