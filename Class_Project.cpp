#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <thread>

#include "Sort.h"
#include "Map_Tokenizer.h"
#include "File_Management.h"
#include "Reduce.h"

// temp testing functions
#include <iostream>
#include <ctime>

// Globals
clock_t start_time; // Global for tic-toc functions
char cwd[4096]; // Global for get current Dir

// Function Definitions

void tic(void) {

    start_time = clock();

}

void toc() {

    clock_t t = clock();
    t = t - start_time;
    double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("This code block took %f seconds to execute \n", time_taken);

}


using namespace std;
namespace fs = std::filesystem;

int workflow(File_Management my_File_Management);
void Map_For_Threads(File_Management my_File_Management, vector<string> inputFiles, string mapdllPathandName, int threadID);
void Reduce_For_Threads(File_Management my_File_Management, vector<string> inputFiles, int i);

int main()
{
    //tic();
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
    //toc();
}

int workflow(File_Management my_File_Management)
{
    vector<string> inputFiles = my_File_Management.getInputFiles();
    string mapdllPathandName = my_File_Management.getDLLFileLocation();
    mapdllPathandName.append("//mapDLL.dll");


    //=============================================================================================
    const int numThreads = 17;
    thread threads[numThreads];

    cout << endl << "Starting Map Section" << endl;
    cout << "==========================================" << endl;

    tic();
    // Create multiple threads
    for (int i = 0; i < numThreads; ++i) {
        cout << "Map Threat Create: " << i + 1 << std::endl;
        threads[i] = thread(Map_For_Threads, my_File_Management, inputFiles, mapdllPathandName, i);
    }

    // Wait for all threads to finish execution
    for (int i = 0; i < numThreads; ++i) {
        threads[i].join();
    }

    cout << "All Map threads have completed their execution" << endl;
    cout << "==========================================" << endl << endl;
    
    //=============================================================================================
    
    cout << "Starting Sort Section" << endl;
    cout << "==========================================" << endl;
    cout << "SORTING FILES" << endl;

    for (int i = 0; i < numThreads; i++)
    {
        my_File_Management.setFileBeingWorked(inputFiles[i]);
        // Sort
        Sort sortObj(my_File_Management); // Looks like constructor runs sort operation
        sortObj.runSort();
    }

    cout << "==========================================" << endl << endl;

    //=============================================================================================
    
    cout << "Starting Reduce Section" << endl;
    cout << "==========================================" << endl;

    // Create multiple threads
    for (int i = 0; i < numThreads; ++i) {
        cout << "Reduce Threat Create: " << i + 1 << std::endl;
        threads[i] = thread(Reduce_For_Threads, my_File_Management, inputFiles, i);
    }

    // Wait for all threads to finish execution
    for (int i = 0; i < numThreads; ++i) {
        threads[i].join();
    }
    
    cout << "All Reduce threads have completed their execution" << endl;
    cout << "==========================================" << endl;
    toc();
    cout << endl;
    
    //=============================================================================================















    /*

    // loop though each input file
    for (int i = 0;  i < my_File_Management.getNumberOfInputFiles(); i++)
    {

        my_File_Management.setFileBeingWorked(inputFiles[i]);
        /*
        tic();
        my_File_Management.setFileBeingWorked(inputFiles[i]);

        // Map
        Map_Tokenizer mapTokenizerObj(my_File_Management);
        vector<string> fileParsedLineVector = my_File_Management.importMapFile();

        // Create file path/name for saving each intermediate file
        string fileName = my_File_Management.getFileBeingWorked();
        
        //cout << my_File_Management.getIntermediateFileLocation();
        
        string interFilePath = my_File_Management.getIntermediateFileLocation();
        interFilePath.append("\\").append("map_").append(fileName);

        // Map
        mapTokenizerObj.runMap(mapdllPathandName, interFilePath, fileParsedLineVector);


        toc();
        

        // Sort
        //cout << "entering sort\n";
        Sort sortObj(my_File_Management); // Looks like constructor runs sort operation
        sortObj.runSort();
        
        // Reduce
        //cout << "entering reduce\n";
        //vector<string> inputFileText = my_File_Management.importReduceFile();
        Reduce reduceObj(my_File_Management);
        reduceObj.reduceCallDLL();
        //vector<string> Test_Reduce_Input_Vector = my_File_Management.importReduceFile();

        std::cout << "File " << i+1 << " complete.\n";

    }

    */

    return 0;

}




void Map_For_Threads(File_Management my_File_Management, vector<string> inputFiles, string mapdllPathandName, int i)
{

    

    //for (int i = 0; i < my_File_Management.getNumberOfInputFiles(); i++)
    //{

        //tic();
        my_File_Management.setFileBeingWorked(inputFiles[i]);

        // Map
        Map_Tokenizer mapTokenizerObj(my_File_Management);
        vector<string> fileParsedLineVector = my_File_Management.importMapFile();

        // Create file path/name for saving each intermediate file
        string fileName = my_File_Management.getFileBeingWorked();

        //cout << my_File_Management.getIntermediateFileLocation();

        string interFilePath = my_File_Management.getIntermediateFileLocation();
        interFilePath.append("\\").append("map_").append(fileName);

        // Map
        mapTokenizerObj.runMap(mapdllPathandName, interFilePath, fileParsedLineVector);


        //toc();
    //}
}





void Reduce_For_Threads(File_Management my_File_Management, vector<string> inputFiles, int i)
{

    

    my_File_Management.setFileBeingWorked(inputFiles[i]);

    //for (int i = 0; i < my_File_Management.getNumberOfInputFiles(); i++)
    //{

    Reduce reduceObj(my_File_Management);
    reduceObj.reduceCallDLL();


    //toc();
//}
}