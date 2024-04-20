#include <iostream>
#include <sys/stat.h>


#include "Map.h"


using namespace std;

int DEBUG = 1;

int main()
{
    string inputFileLocation;
    string outputFileLocation;
    string intermediateFileLocation;
    
    if (DEBUG == 1)
    {
        /*
        //inputFileLocation = R"(C:\Users\tpesp\OneDrive\Documents\Masters\Classes\4_Spring_2024\2_Wed_Object_Oriented_Design\Projects\Supporting_Folders\Input_Files)";
        //outputFileLocation = R"C:\Users\tpesp\OneDrive\Documents\Masters\Classes\4_Spring_2024\2_Wed_Object_Oriented_Design\Projects\Supporting_Folders\Output_Files)";
        //intermediateFileLocation = R"(C:\Users\tpesp\OneDrive\Documents\Masters\Classes\4_Spring_2024\2_Wed_Object_Oriented_Design\Projects\Supporting_Folders\Intermediate_Files)";
    
        struct stat sb;

        // Calls the function with path as argument
        // If the file/directory exists at the path returns 0
        // If block executes if path exists
        if (stat(inputFileLocation, &sb) == 0)
            cout << "The path is valid!";
        else
            cout << "The Path is invalid!";
            */
    }
    else
    {
        cout << "Provide a URL for the following directories\n";
        cout << "Input: ";
        cin >> inputFileLocation;
        cout << "Output: ";
        cin >> outputFileLocation;
        cout << "Intermidiate: ";
        cin >> intermediateFileLocation;
    }
    

    Map myMap(5);

    myMap.this_is_DUMB();
}
