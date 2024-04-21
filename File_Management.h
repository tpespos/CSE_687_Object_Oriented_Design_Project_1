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




	bool isFileEmpty(const string& filename);

	string extractFileName(const string& filePath);



	vector<string> importMapFile();

	vector<string> importSortFile();

	vector<string> importReduceFile();



	void exportMapFile(const vector<string>& data);

	void exportSortFile(const vector<string>& data);

	void exportReduceFile(const vector<string>& data);






	vector<string> getInputFiles();

	vector<string> getIntermediateFiles();



	void setFileBeingWorked(string filePath);


private:

	string fileBeingWorked;



	string inputFileLocation;

	vector<string> inputFiles;

	string outputFileLocation;

	string intermediateFileLocation;

	vector<string> intermediateFiles;




};

