#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <pch.h>

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

int File_Management::getNumberOfInputFiles()
{
	return nInputFiles;
}

string File_Management::getIntermediateFileLocation()
{
	return getIntermediateFileLocation();
}


//================================================================
//================================================================
//================================================================

vector<string> File_Management::importReduceFile() 
{
	vector<string> lines;
	string intermediateFilePath = intermediateFileLocation;
	string filepath = intermediateFilePath.append("\\").append("Sort_").append(fileBeingWorked);
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
	string filepath = intermediateFilePath.append("\\").append("Map_").append(fileBeingWorked);
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
	vector<string> lines;
	string inputFilePath = inputFileLocation;
	string filepath = inputFilePath.append("\\").append(fileBeingWorked);

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

void File_Management::exportMapFile(string intermediateFileLocation, const vector<string>& data)
{
	ofstream file;
	string filepath = intermediateFileLocation;

	//string filepath = intermediateFilePath.append("\\").append("Map_").append("Stuff");
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
	string filepath = intermediateFilePath.append("\\").append("Sort_").append(fileBeingWorked);
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

void File_Management::outputSuccessFile()
{
	ofstream file;
	string outputFilePath = outputFileLocation;
	string filepath = outputFilePath.append("\\").append("SUCCESS.txt");
	file.open(filepath);

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

	nInputFiles = inputFiles.size();

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

vector<string> File_Management::getDllFiles()
{
	//added by ryan
	return dllFiles;
}

string File_Management::getDLLFileLocation()
{
	return dllFileLocation;
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


void File_Management::setInputFileLocation(string filepath)
{
	inputFileLocation = filepath;
}

void File_Management::setIntermediateFileLocation(string filepath)
{
	intermediateFileLocation = filepath;
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

int File_Management::searchThroughDllDirectory()
{
	int numberOfCorrectDllFiles = 0;

	// search for files inside of the input file directory and append them to the inputfiles vector
	for (const auto& entry : fs::directory_iterator(dllFileLocation))
	{
		if (entry.is_regular_file()) {
			dllFiles.push_back(entry.path().string());
		}
	}

	/*
	if (DEBUG == 1)	{
		cout << "\nFILES FOUND: \n";
		for (int i = 0; i < dllFiles.size(); i++)		{
			cout << dllFiles[i]<< "\n";
		}
		cout << "\n";
	}
	//*/
	
	
	for (auto file : dllFiles)
	{
		
		file = file.substr(file.find_last_of("\\") + 1, file.length() - file.find_last_of("\\"));
		
		if (file == "Map_DLL.dll")
		{
			numberOfCorrectDllFiles++;
			break;
		}
	}
	
	for (auto file : dllFiles)
	{
		file = file.substr(file.find_last_of("\\") + 1, file.length() - file.find_last_of("\\"));
		if (file == "ReduceDLL.dll")
		{
			numberOfCorrectDllFiles++;
			break;
		}
	}
	
	if (numberOfCorrectDllFiles != 2)
	{
		cout << "Desired DLL Files NOT FOUND!" << endl; //Exiting the program" << endl;
		return 0;
	}

	return 1;
}

//================================================================
//================================================================
//================================================================

void File_Management::promptUserForDirectories()
{
	/////////////////////////////////////////////////////////////////////////////////////////////////////REMOVE DEBUG HERE!!!!!
	DEBUG = 1;


	struct stat sb;

	cout << "Provide a URL for the following directories\n";

	//=====================================================
	
	cout << "Input: ";
	if (DEBUG == 1)	{
		inputFileLocation = "C:\\Users\\lande\\source\\repos\\tpespos\\CSE_687_Object_Oriented_Design_Project_1\\Plays\\Plays";
	}
	else
	{
		cin >> inputFileLocation;
	}
	

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
	if (DEBUG == 1) {
		outputFileLocation = "C:\\Users\\lande\\source\\repos\\tpespos\\CSE_687_Object_Oriented_Design_Project_1\\Plays\\Output";
	}
	else
	{
		cin >> outputFileLocation;
	}


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
	if (DEBUG == 1) {
		intermediateFileLocation = "C:\\Users\\lande\\source\\repos\\tpespos\\CSE_687_Object_Oriented_Design_Project_1\\Plays\\Interm";
	}
	else
	{
		cin >> intermediateFileLocation;
	}

	dir = intermediateFileLocation.c_str();

	while (stat(dir, &sb) != 0)
	{
		cout << "ERROR: Enter Valid Input Directory: ";
		cin >> intermediateFileLocation;
		dir = intermediateFileLocation.c_str();
	}

	cout << endl;

	//=====================================================

	int didWeFindTheRightDllFiles = 0;
	int numberOfTimesThroughLoop = 0;
	while (didWeFindTheRightDllFiles == 0)
	{
		cout << "DLL: ";
		if (DEBUG == 1 && numberOfTimesThroughLoop == 0) {
			dllFileLocation = "C:\\Users\\lande\\source\\repos\\tpespos\\CSE_687_Object_Oriented_Design_Project_1\\DLLs";
			//dllFileLocation = "C:\\Users\\lande\\OneDrive\\Documents\\!Masters\\DLLs";
		
		}
		else
		{
			cin >> dllFileLocation;
		}

		dir = dllFileLocation.c_str();

		while (stat(dir, &sb) != 0)
		{
			cout << "ERROR: Enter Valid Input Directory: ";
			cin >> dllFileLocation;
			dir = dllFileLocation.c_str();
		}

		cout << endl;
		
		//exit(0);
		didWeFindTheRightDllFiles = searchThroughDllDirectory();
		numberOfTimesThroughLoop++;
	}

}

