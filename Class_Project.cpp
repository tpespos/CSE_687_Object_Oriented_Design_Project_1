#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include <sys/stat.h>

#include "Sort.h"
#include "Map_Tokenizer.h"
#include "File_Management.h"
#include "Reduce.h"

// temp testing functions
#include <iostream>
#include <ctime>

//// Globals
//clock_t start_time; // Global for tic-toc functions
//char cwd[4096]; // Global for get current Dir
//
//// Function Definitions
//
//void tic(void) {
//
//    start_time = clock();
//
//}
//
//void toc() {
//
//    clock_t t = clock();
//    t = t - start_time;
//    double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
//    printf("This code block took %f seconds to execute \n", time_taken);
//
//}
//

using namespace std;
namespace fs = std::filesystem;

int workflow(File_Management my_File_Management);

int main()
{
    File_Management my_File_Management;
    Reduce myReducer;

    my_File_Management.promptUserForDirectories();
    
    int check = workflow(my_File_Management);
    if (check)
    {
        std::cout << "Failure in workflow.\n";
        return 1;
    }

    std::cout << "End Program" << std::endl;

}

int workflow(File_Management my_File_Management)
{
    vector<string> inputFiles = my_File_Management.getInputFiles();

    // loop though each input file
    for (int i = 0;  i < my_File_Management.getNumberOfInputFiles(); i++)
    {
        //tic();
        my_File_Management.setFileBeingWorked(inputFiles[i]);

        // Map
        Map_Tokenizer mapTokenizerObj(my_File_Management);
        vector<string> fileParsedLineVector = my_File_Management.importMapFile();
        string fileName = my_File_Management.getFileBeingWorked();
        for (int i = 0; i < fileParsedLineVector.size(); i++)
        {
            mapTokenizerObj.map(fileName, fileParsedLineVector[i]);
        }
        mapTokenizerObj.writeTofile();

        //toc();
        // Sort
        //cout << "entering sort\n";
        Sort sortObj(my_File_Management); // Looks like constructor runs sort operation
        sortObj.runSort();
        
        // Reduce
        //cout << "entering reduce\n";
        Reduce reduceObj(my_File_Management);
        reduceObj.reduceWrapper();
        //vector<string> Test_Reduce_Input_Vector = my_File_Management.importReduceFile();

        std::cout << "Loop " << i << " complete.\n";

    }

    return 0;

}