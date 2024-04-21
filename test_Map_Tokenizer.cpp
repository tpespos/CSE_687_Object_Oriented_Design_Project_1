

// test the map tokenizer class

#include "File_Management.h"
#include "Map_Tokenizer.h"

int main(void)
{

	File_Management inputFileObj;
	Map_Tokenizer mapTokenizerObj(inputFileObj);
	inputFileObj.setFileBeingWorked("inputFile1.txt");

	string currentLine = " ode to my poor coding skills! Time to cry...";

	mapTokenizerObj.map(inputFileObj.getFileBeingWorked(), currentLine);









}