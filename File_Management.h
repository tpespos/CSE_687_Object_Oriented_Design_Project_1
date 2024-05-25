#pragma once



#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sys/stat.h>
#include "framework.h"
//test

using namespace std;

class File_Management
{

public:

	void promptUserForDirectories();
	 
	void readConfigFileForDirectories();

	void searchThroughInputDirectory();

	void searchThroughIntermediateDirectory();

	int searchThroughDllDirectory();

	static bool isFileEmpty(const string& filename);

	string extractFileName(const string& filePath);

	vector<string> importMapFile();

	vector<string> importSortFile(string fileNumber, string partNumber, bool thisIsTheFinalSortFile);

	vector<string> importReduceFile(string partNumber, bool thisIsTheFinalOutputFile);

	//static 
	void exportMapFile(string fileNumber, string partNumber, const vector<string>& data);

	void exportSortFile(string partNumber, const vector<string>& data, bool thisIsTheFinalSortFile);

	void exportReduceFile(string partNumber, const vector<string>& data, bool finalOutputFile);

	vector<string> getInputFiles();

	vector<string> getIntermediateFiles();

	vector<string> getDllFiles();

	void setInputFileLocation(string filepath);

	void setIntermediateFileLocation(string filepath);

	void setFileBeingWorked(string filePath);

	string getFileBeingWorked();

	int getNumberOfInputFiles();

	string getIntermediateFileLocation();

	string getDLLFileLocation();

	void outputSuccessFile();

private:

	string fileBeingWorked;

	int nInputFiles = 0;

	string inputFileLocation;

	vector<string> inputFiles;

	string outputFileLocation;

	string intermediateFileLocation = "";

	string dllFileLocation;

	vector<string> dllFiles;

	vector<string> intermediateFiles;

	int DEBUG;

	string relativeConfigFileLocation;

};

