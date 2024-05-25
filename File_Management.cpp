#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sys/stat.h>
#include "framework.h"

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
	return intermediateFileLocation;
}


//================================================================
//================================================================
//================================================================

vector<string> File_Management::importReduceFile(string partNumber)
{
	vector<string> lines;
	string intermediateFilePath = intermediateFileLocation;
	string filepath = intermediateFilePath.append("\\").append("S").append(partNumber).append(".txt");
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


vector<string> File_Management::importSortFile(string fileNumber, string partNumber)
{
	vector<string> lines;
	string intermediateFilePath = intermediateFileLocation;
	string filepath = intermediateFilePath.append("\\").append("M").append(fileNumber).append(partNumber).append(".txt");
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

void File_Management::exportMapFile(string fileNumber, string partNumber, const vector<string>& data)
{
	ofstream file;
	string intermediateFilePath = intermediateFileLocation;
	string filepath = intermediateFilePath.append("\\").append("M").append(fileNumber).append(partNumber).append(".txt");

	//string filepath = intermediateFileLocation;
	//string outPutFileNameAndPath = intermediateFileLocation;
	//outPutFileNameAndPath.append(fileName);

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

void File_Management::exportSortFile(string partNumber, const vector<string>& data)
{
	ofstream file;
	string intermediateFilePath = intermediateFileLocation;
	string filepath = intermediateFilePath.append("\\").append("S").append(partNumber).append(".txt");
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

void File_Management::exportReduceFile(string partNumber, const vector<string>& data, bool thisIsTheFinalOutputFile)
{
	ofstream file;
	string filepath = "";
	string outputFilePath = "";
	string intermediateFilePath = "";

	if (thisIsTheFinalOutputFile)
	{
		outputFilePath = outputFileLocation;
		filepath = outputFilePath.append("\\").append("Final_Output_File.txt");
	}
	else
	{
		intermediateFilePath = intermediateFileLocation;
		filepath = intermediateFilePath.append("\\").append("R").append(partNumber).append(".txt");
	}

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
		
		if (file == "mapDLL.dll")
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
		//inputFileLocation = "C:\\Users\\lande\\source\\repos\\tpespos\\CSE_687_Object_Oriented_Design_Project_1\\Plays\\Plays";
		//inputFileLocation = "C:\\Users\\lodin\\Documents\\College_work\\Spring2024\\OOD_Wensday_Class\\Project1\\shakespeare";
		inputFileLocation = "C:\\Users\\tpesp\\source\\repos\\CSE-687-Object-Oriented-Design-Project-1\\Plays\\Plays";
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
		//outputFileLocation = "C:\\Users\\lande\\source\\repos\\tpespos\\CSE_687_Object_Oriented_Design_Project_1\\Plays\\Output";
		//outputFileLocation = "C:\\Users\\lodin\\Documents\\College_work\\Spring2024\\OOD_Wensday_Class\\Project1\\out";
		outputFileLocation = "C:\\Users\\tpesp\\source\\repos\\CSE-687-Object-Oriented-Design-Project-1\\Plays\\Output";
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
		//intermediateFileLocation = "C:\\Users\\lande\\source\\repos\\tpespos\\CSE_687_Object_Oriented_Design_Project_1\\Plays\\Interm";
		//intermediateFileLocation = "C:\\Users\\lodin\\Documents\\College_work\\Spring2024\\OOD_Wensday_Class\\Project1\\interFileLoc";
		intermediateFileLocation = "C:\\Users\\tpesp\\source\\repos\\CSE-687-Object-Oriented-Design-Project-1\\Plays\\interm";
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
			//dllFileLocation = "C:\\Users\\lande\\source\\repos\\tpespos\\CSE_687_Object_Oriented_Design_Project_1\\DLLs";
			//dllFileLocation = "C:\\Users\\lodin\\Documents\\College_work\\Spring2024\\OOD_Wensday_Class\\Project1\\code\\DLLs";
			dllFileLocation = "C:\\Users\\tpesp\\source\\repos\\CSE-687-Object-Oriented-Design-Project-1\\DLLs";
		
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


//================================================================
//================================================================
//================================================================

void File_Management::readConfigFileForDirectories()
{
	int numberOfTimesThroughLoop = 0;
	string line;
	struct stat sb;
	relativeConfigFileLocation = "Config_File\\Config.txt";

	ifstream file(relativeConfigFileLocation);
	if (!file.is_open()) {
		cerr << "Failed to open file for reading." << endl;
		return;
	}

	
	while (getline(file, line)) {

		if (numberOfTimesThroughLoop == 0)
		{
			inputFileLocation = line;
			numberOfTimesThroughLoop++;
			
			const char* dir = inputFileLocation.c_str();
			if (stat(dir, &sb) != 0)
			{
				cout << "ERROR: Config File Not Configured Issue with line 1 INPUT FILE LOCATION";
				exit(0);
			}
		}
		else if (numberOfTimesThroughLoop == 1)
		{
			intermediateFileLocation = line;
			numberOfTimesThroughLoop++;

			const char* dir = intermediateFileLocation.c_str();
			if (stat(dir, &sb) != 0)
			{
				cout << "ERROR: Config File Not Configured Issue with line 2 INTERMEDIATE FILE LOCATION";
				exit(0);
			}
		}
		else if (numberOfTimesThroughLoop == 2)
		{
			outputFileLocation = line;
			numberOfTimesThroughLoop++;

			const char* dir = outputFileLocation.c_str();
			if (stat(dir, &sb) != 0)
			{
				cout << "ERROR: Config File Not Configured Issue with line 3 OUTPUT FILE LOCATION";
				exit(0);
			}
		}
		else if (numberOfTimesThroughLoop == 3)
		{
			dllFileLocation = line;
			numberOfTimesThroughLoop++;

			const char* dir = dllFileLocation.c_str();
			if (stat(dir, &sb) != 0)
			{
				cout << "ERROR: Config File Not Configured Issue with line 4 DLL FILE LOCATION";
				exit(0);
			}

			if (searchThroughDllDirectory() == 0)
			{
				cout << "ERROR: The correct DLL files not found in the DLL File Location";
				exit(0);
			}
		}
		
	}

	if (numberOfTimesThroughLoop != 4)
	{
		cout << "ERROR: There are more or less than 4 lines in the config file, fix your config file.";
		exit(0);
	}

	file.close();

}