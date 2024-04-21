#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sys/stat.h>

#include "File_Management.h"

using namespace std;
namespace fs = std::filesystem;

//================================================================
//================================================================
//================================================================

void File_Management::exportToFile(const vector<string>& data, const string& filename) {
	ofstream file;
	if (isFileEmpty(filename)) {
		file.open(filename);
	}
	else {
		file.open(filename, ios::app); // Open file in append mode
		file << endl; // Add a newline to separate appended data
	}

	if (!file.is_open()) {
		cerr << "Failed to open file for writing." << endl;
		return;
	}

	for (size_t i = 0; i < data.size(); ++i) {
		file << data[i];
		if (i != data.size() - 1) {
			file << endl;
		}
	}

	file.close();
}

//================================================================
//================================================================
//================================================================


// check the first charicter of the file, and check if it's the end of file character
bool File_Management::isFileEmpty(const string& filename) {
	ifstream file(filename);
	return file.peek() == ifstream::traits_type::eof();
}

//================================================================
//================================================================
//================================================================

vector<string> File_Management::getInputFiles()
{
	searchThroughInputDirectory();

	return inputFiles;
}

//================================================================
//================================================================
//================================================================

vector<string> File_Management::getIntermediateFiles()
{
	searchThroughIntermediateDirectory();

	return intermediateFiles;
}

//================================================================
//================================================================
//================================================================

void File_Management::searchThroughIntermediateDirectory()
{

	// search for files inside of the input file directory and append them to the inputfiles vector
	for (const auto& entry : fs::directory_iterator(intermediateFileLocation)) {
		if (entry.is_regular_file()) {
			intermediateFiles.push_back(entry.path().string());
		}
	}

}

//================================================================
//================================================================
//================================================================

void File_Management::searchThroughInputDirectory()
{

	// search for files inside of the input file directory and append them to the inputfiles vector
	for (const auto& entry : fs::directory_iterator(inputFileLocation)) {
		if (entry.is_regular_file()) {
			inputFiles.push_back(entry.path().string());
		}
	}

}

//================================================================
//================================================================
//================================================================

void File_Management::promptUserForDirectories()
{

	struct stat sb;

	cout << "Provide a URL for the following directories\n";

	//=====================================================

	cout << "Input: ";
	cin >> inputFileLocation;

	const char* dir = inputFileLocation.c_str();

	while (stat(dir, &sb) != 0)
	{
		cout << "ERROR: Enter Valid Input Directory: ";
		cin >> inputFileLocation;
		const char* dir = inputFileLocation.c_str();
	}

	//=====================================================

	cout << "Output: ";
	cin >> outputFileLocation;

	const char* dir = outputFileLocation.c_str();

	while (stat(dir, &sb) != 0)
	{
		cout << "ERROR: Enter Valid Input Directory: ";
		cin >> outputFileLocation;
		const char* dir = outputFileLocation.c_str();
	}

	//=====================================================

	cout << "Intermidiate: ";
	cin >> intermediateFileLocation;

	const char* dir = intermediateFileLocation.c_str();

	while (stat(dir, &sb) != 0)
	{
		cout << "ERROR: Enter Valid Input Directory: ";
		cin >> intermediateFileLocation;
		const char* dir = intermediateFileLocation.c_str();
	}

}

