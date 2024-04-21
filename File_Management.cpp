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

void File_Management::setFileBeingWorked(string filePath)
{

	string file = extractFileName(filePath);

	fileBeingWorked = file;

}

string File_Management::getFileBeingWorked()
{
	return fileBeingWorked;
}


//================================================================
//================================================================
//================================================================

string File_Management::extractFileName(const string& filePath) 
{

	fs::path path(filePath);
	return path.filename().string();

}


//================================================================
//================================================================
//================================================================

vector<string> File_Management::importReduceFile() 
{
	vector<string> lines;
	string intermediateFilePath = intermediateFileLocation;
	string filepath = intermediateFilePath.append("\\").append("Sort.txt");
	ifstream file(filepath);
	if (!file.is_open()) {
		cerr << "Failed to open file for reading." << endl;
		return lines;
	}

	string line;
	while (getline(file, line)) {
		lines.push_back(line);
	}

	file.close();
	return lines;
}


//================================================================
//================================================================
//================================================================


vector<string> File_Management::importSortFile() 
{
	vector<string> lines;
	string intermediateFilePath = intermediateFileLocation;
	string filepath = intermediateFilePath.append("\\").append("Map.txt");
	ifstream file(filepath);
	if (!file.is_open()) {
		cerr << "Failed to open file for reading." << endl;
		return lines;
	}

	string line;
	while (getline(file, line)) {
		lines.push_back(line);
	}

	file.close();
	return lines;
}


//================================================================
//================================================================
//================================================================


vector<string> File_Management::importMapFile() 
{
	vector<string> words;
	string inputFilePath = inputFileLocation;
	string filepath = inputFilePath.append("\\").append(fileBeingWorked);

	ifstream file(filepath);
	if (!file.is_open()) {
		cerr << "Failed to open file for reading." << endl;
		return words;
	}

	string word;
	while (file >> word) {
		words.push_back(word);
	}

	file.close();
	return words;
}

//================================================================
//================================================================
//================================================================

void File_Management::exportMapFile(const vector<string>& data) 
{
	ofstream file;
	string intermediateFilePath = intermediateFileLocation;
	string filepath = intermediateFilePath.append("\\").append("Map.txt");
	if (isFileEmpty(filepath)) {
		file.open(filepath);
	}
	else {
		file.open(filepath, ios::app); // Open file in append mode
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

void File_Management::exportSortFile(const vector<string>& data) 
{
	ofstream file;
	string intermediateFilePath = intermediateFileLocation;
	string filepath = intermediateFilePath.append("\\").append("Sort.txt");
	if (isFileEmpty(filepath)) {
		file.open(filepath);
	}
	else {
		file.open(filepath, ios::app); // Open file in append mode
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

void File_Management::exportReduceFile(const vector<string>& data) 
{
	ofstream file;
	string outputFilePath = outputFileLocation;
	string filepath = outputFilePath.append("\\").append(fileBeingWorked);
	if (isFileEmpty(filepath)) {
		file.open(filepath);
	}
	else {
		file.open(filepath, ios::app); // Open file in append mode
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
bool File_Management::isFileEmpty(const string& filename) 
{
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
	for (const auto& entry : fs::directory_iterator(intermediateFileLocation)) 
	{
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
	for (const auto& entry : fs::directory_iterator(inputFileLocation)) 
	{
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
		dir = inputFileLocation.c_str();
	}

	cout << endl;

	//=====================================================

	cout << "Output: ";
	cin >> outputFileLocation;

	dir = outputFileLocation.c_str();

	while (stat(dir, &sb) != 0)
	{
		cout << "ERROR: Enter Valid Input Directory: ";
		cin >> outputFileLocation;
		dir = outputFileLocation.c_str();
	}

	cout << endl;

	//=====================================================

	cout << "Intermidiate: ";
	cin >> intermediateFileLocation;

	dir = intermediateFileLocation.c_str();

	while (stat(dir, &sb) != 0)
	{
		cout << "ERROR: Enter Valid Input Directory: ";
		cin >> intermediateFileLocation;
		dir = intermediateFileLocation.c_str();
	}

	cout << endl;

}

