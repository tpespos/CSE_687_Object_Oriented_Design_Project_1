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

    bool TEST = 1;
    if (!TEST)
    {
        my_File_Management.promptUserForDirectories();
    }
    else
    {
        string inputPath = "C:\\Users\\lodin\\Documents\\College_work\\Spring2024\\OOD_Wensday_Class\\Project1\\shakespeare";
        string ouputPath = "C:\\Users\\lodin\\Documents\\College_work\\Spring2024\\OOD_Wensday_Class\\Project1\\out";
        string interPath = "C:\\Users\\lodin\\Documents\\College_work\\Spring2024\\OOD_Wensday_Class\\Project1\\interFileLoc";
        string dllPath = "C:\\Users\\lodin\\Documents\\College_work\\Spring2024\\OOD_Wensday_Class\\Project1\\code\\x64\\Debug";
        my_File_Management.setInputFileLocation(inputPath);
        my_File_Management.setOutputFileLocation(ouputPath);
        my_File_Management.setIntermediateFileLocation(interPath);
        my_File_Management.setDLLFileLocation(dllPath);

    }
 
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
    string mapdllPathandName = my_File_Management.getDLLFileLocation();
    mapdllPathandName.append("//mapDLL.dll");

    // loop though each input file
    for (int i = 0;  i < my_File_Management.getNumberOfInputFiles(); i++)
    {
        //tic();
        my_File_Management.setFileBeingWorked(inputFiles[i]);

        // Map
        Map_Tokenizer mapTokenizerObj(my_File_Management);
        vector<string> fileParsedLineVector = my_File_Management.importMapFile();

        // Create file path/name for saving each intermediate file
        string fileName = my_File_Management.getFileBeingWorked();
        string interFilePath = my_File_Management.getIntermediateFileLocation();
        interFilePath.append("\\").append("map_").append(fileName);

        for (int i = 0; i < fileParsedLineVector.size(); i++)
        {
            mapTokenizerObj.mapDLL(mapdllPathandName, interFilePath, fileParsedLineVector[i]);
        }
 
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

        std::cout << "File " << i+1 << " complete.\n";

    }

    return 0;

}