#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sys/stat.h>

using namespace std;

class File_Management
{

public:

	void promptUserForDirectories();

	void searchThroughInputDirectory();

	void searchThroughIntermediateDirectory();

	int searchThroughDllDirectory();

	bool isFileEmpty(const string& filename);

	string extractFileName(const string& filePath);

	vector<string> importMapFile();

	vector<string> importSortFile();

	vector<string> importReduceFile();

	//void exportMapFile(const vector<string>& data);
	static void exportMapFile(string intermediateFileLocation, const vector<string>& data);

	void exportSortFile(const vector<string>& data);

	void exportReduceFile(const vector<string>& data);

	vector<string> getInputFiles();

	vector<string> getIntermediateFiles();

	void setInputFileLocation(string filepath);

	void setIntermediateFileLocation(string filepath);

	void setFileBeingWorked(string filePath);

	string getFileBeingWorked();

	int getNumberOfInputFiles();

	string getInputFileLocation();

	void outputSuccessFile();

private:

	string fileBeingWorked;

	int nInputFiles = 0;

	string inputFileLocation;

	vector<string> inputFiles;

	string outputFileLocation;

	string intermediateFileLocation;

	string dllFileLocation;

	vector<string> dllFiles;

	vector<string> intermediateFiles;

};

