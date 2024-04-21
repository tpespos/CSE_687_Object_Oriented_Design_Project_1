#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include <sys/stat.h>


#include "Map_Tokenizer.h"
#include "File_Management.h"


using namespace std;
namespace fs = std::filesystem;


int main()
{
        
    File_Management my_File_Management;

    // Sample text file would look like this        a the is the a
    // This section happens outside of loop that iterates over all files in the input directory
    //my_File_Management.promptUserForDirectories();

    // hardcodeing for testing (change to your local file location to quick testing)
    string filepath1 = "C:\\Users\\lodin\\Documents\\College_work\\Spring2024\\OOD_Wensday_Class\\Project1\\shakespeare";
    string filepath2 = "C:\\Users\\lodin\\Documents\\College_work\\Spring2024\\OOD_Wensday_Class\\Project1\\interFileLoc";
    my_File_Management.setInputFileLocation(filepath1);
    my_File_Management.setIntermediateFileLocation(filepath2);

    vector<string> inputFiles = my_File_Management.getInputFiles();

    // this line needs to be the first line in the loop that iterates over all files in the input directory

    for (int i = 0; i < my_File_Management.getNumberOfInputFiles(); i++)
    {
        my_File_Management.setFileBeingWorked(inputFiles[i]);
        Map_Tokenizer mapTokenizerObj(my_File_Management);
        mapTokenizerObj.parseLines();
    }
    


    //****************
    // This part happens inside of the Map Class
    //my_File_Management.setFileBeingWorked("inputFile1.txt");
 
    //vector<string> Test_Map_Input_Vector = my_File_Management.importMapFile();

    //string currentLine = " ode to my poor coding skills! Time to cry...";

    //mapTokenizerObj.map(my_File_Management.getFileBeingWorked(), currentLine);

    //vector<string> Test_Map_Input_Vector = my_File_Management.importMapFile();
    // DO WORK
    //vector<string> Test_Map_Output_Vector = { "(“a”, 1)", "(“the”, 1)", "(“is”, 1)", "(“the”, 1)", "(“a”, 1)" };
    //my_File_Management.exportMapFile(Test_Map_Output_Vector);
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