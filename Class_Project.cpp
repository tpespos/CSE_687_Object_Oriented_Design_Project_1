#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include <sys/stat.h>


#include "Map.h"
#include "File_Management.h"


using namespace std;
namespace fs = std::filesystem;

int DEBUG = 0;

int main()
{

    if (DEBUG == 1)
    {
        string inputFileLocation;
        string outputFileLocation;
        string intermediateFileLocation;

        //const char* dir = "C:/Users/tpesp";
        const char* dir = "C:\\Users\\tpesp\\OneDrive\\Documents\\Masters\\Classes\\4_Spring_2024\\2_Wed_Object_Oriented_Design\\Projects\\Supporting_Folders\\Input_Files";
        inputFileLocation = "C:\\Users\\tpesp\\OneDrive\\Documents\\Masters\\Classes\\4_Spring_2024\\2_Wed_Object_Oriented_Design\\Projects\\Supporting_Folders\\Input_Files";
        outputFileLocation = "C:\\Users\\tpesp\\OneDrive\\Documents\\Masters\\Classes\\4_Spring_2024\\2_Wed_Object_Oriented_Design\\Projects\\Supporting_Folders\\Output_Files";
        intermediateFileLocation = "C:\\Users\\tpesp\\OneDrive\\Documents\\Masters\\Classes\\4_Spring_2024\\2_Wed_Object_Oriented_Design\\Projects\\Supporting_Folders\\Intermediate_Files";
    
        struct stat sb;

        // Calls the function with path as argument
        // If the file/directory exists at the path returns 0
        // If block executes if path exists
        const char* dirt = inputFileLocation.c_str();

        if (stat(dirt, &sb) == 0)
            cout << "The path is valid!\n";
        else
            cout << "The Path is invalid!\n";


        
        for (const auto& entry : fs::directory_iterator(inputFileLocation)) {

            // Converting the path to const char * in the
            // subsequent lines
            std::filesystem::path outfilename = entry.path();
            std::string outfilename_str = outfilename.string();
            const char* path = outfilename_str.c_str();

            // Testing whether the path points to a
            // non-directory or not If it does, displays path
            if (stat(path, &sb) == 0 && !(sb.st_mode & S_IFDIR))
                std::cout << path << std::endl;
        }
            
    }
    else
    {
        
        File_Management my_File_Management;

        my_File_Management.promptUserForDirectories();
    }
    

    Map myMap(5);

    myMap.this_is_DUMB();
}