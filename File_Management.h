#pragma once

#include <string>
using std::namespace;

class File_Management
{

public:
	int setPath(string input);

	int setPlayFilename(string input);

	int setTempFilename(string input);

	string getPath();

	string getPlayFilename();

	string getTempFilename();


private:

	//main play text path
	string path;
	
	//main play filename
	string playFilaname;
	
	//temp file for post-map transfer to reduce class
	string tempFilename;

	
};

