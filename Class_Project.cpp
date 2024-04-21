#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include <sys/stat.h>


#include "Map.h"
#include "File_Management.h"


using namespace std;
namespace fs = std::filesystem;


int main()
{
        
    File_Management my_File_Management;

    // Sample text file would look like this        a the is the a
    // This section happens outside of loop that iterates over all files in the input directory
    my_File_Management.promptUserForDirectories();
    vector<string> inputFiles = my_File_Management.getInputFiles();

    // this line needs to be the first line in the loop that iterates over all files in the input directory
    my_File_Management.setFileBeingWorked(inputFiles[0]);


    //****************
    // This part happens inside of the Map Class
    vector<string> Test_Map_Input_Vector = my_File_Management.importMapFile();
    // DO WORK
    vector<string> Test_Map_Output_Vector = { "(“a”, 1)", "(“the”, 1)", "(“is”, 1)", "(“the”, 1)", "(“a”, 1)" };
    my_File_Management.exportMapFile(Test_Map_Output_Vector);
    //****************


    //################
    // This part happens inside of the Sort Class
    vector<string> Test_Sort_Input_Vector = my_File_Management.importSortFile();
    // DO WORK
    vector<string> Test_Sort_Output_Vector = { "(“a”,[1, 1, 1])", "(“the”,[1, 1])", "(“is”,[1])" };
    my_File_Management.exportSortFile(Test_Sort_Output_Vector);
    //################


    //@@@@@@@@@@@@@@@@
    // This part happens inside of the Reduce Class
    vector<string> Test_Reduce_Input_Vector = my_File_Management.importReduceFile();
    // DO WORK
    vector<string> Test_Reduce_Output_Vector = { "(“a”,3)", "(“the”,2)", "(“is”,1)" };
    my_File_Management.exportReduceFile(Test_Reduce_Output_Vector);
    //@@@@@@@@@@@@@@@@
}