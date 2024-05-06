

#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "framework.h"

#include "File_Management.h"
using namespace std;


class Reduce
{

public:
	//constructor
	Reduce();
	Reduce(File_Management files);

	//destructor


	//methods
	int reduceCallDLL();

	int fileManagerUpdate(File_Management newFileManeger);


private:
	//vars

	//string inputFileName;
	File_Management fileManager;

	int DEBUG;

};

