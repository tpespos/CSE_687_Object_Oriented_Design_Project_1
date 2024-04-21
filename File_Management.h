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

	void exportToFile(const vector<string>& data, const string& filename);



	vector<string> getInputFiles();

	vector<string> getIntermediateFiles();


private:





	string inputFileLocation;

	vector<string> inputFiles;

	string outputFileLocation;

	string intermediateFileLocation;

	vector<string> intermediateFiles;




};

