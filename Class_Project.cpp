#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include <sys/stat.h>

#include "Sort.h"
#include "Map_Tokenizer.h"
#include "File_Management.h"
#include "Reduce.h"


using namespace std;
namespace fs = std::filesystem;

int workflow();

int main()
{
        
    int check = workflow();
    if (check)
    {
        std::cout << "Failure in workflow.\n";
        return 1;
    }

    std::cout << "End Program" << std::endl;

}

int workflow()
{

    File_Management my_File_Management;
    Reduce myReducer;

    // Commenting out for testing
    //my_File_Management.promptUserForDirectories();
    //vector<string> inputFiles = my_File_Management.getInputFiles();

    // hardcodeing for testing (change to your local file location to quick testing)
    string filepath1 = "C:\\Users\\lodin\\Documents\\College_work\\Spring2024\\OOD_Wensday_Class\\Project1\\shakespeare";
    string filepath2 = "C:\\Users\\lodin\\Documents\\College_work\\Spring2024\\OOD_Wensday_Class\\Project1\\interFileLoc";
    my_File_Management.setInputFileLocation(filepath1);
    my_File_Management.setIntermediateFileLocation(filepath2);

    vector<string> inputFiles = my_File_Management.getInputFiles();

    // loop though each input file
    for (int i = 0; i < my_File_Management.getNumberOfInputFiles(); i++)
    {
        my_File_Management.setFileBeingWorked(inputFiles[i]);

        // Map
        Map_Tokenizer mapTokenizerObj(my_File_Management);
        vector<string> fileParsedLineVector = my_File_Management.importMapFile();
        string fileName = my_File_Management.getFileBeingWorked();
        for (int i = 0; i < fileParsedLineVector.size(); i++)
        {
            mapTokenizerObj.map(fileName, fileParsedLineVector[i]);
        }

   



        // Sort


        // Reduce


        std::cout << "Loop " << i << " complete.\n";

    }

    //################
    // This part happens inside of the Sort Class
    //vector<string> Test_Sort_Input_Vector = my_File_Management.importSortFile();
    //// DO WORK
    //Sort test_sort_class(my_File_Management);
    //vector<string> Test_Sort_Output_Vector = { "(“a”,[1, 1, 1])", "(“the”,[1, 1])", "(“is”,[1])" };
    //my_File_Management.exportSortFile(Test_Sort_Output_Vector);
    //################


    //@@@@@@@@@@@@@@@@
    // This part happens inside of the Reduce Class
    //vector<string> Test_Reduce_Input_Vector = my_File_Management.importReduceFile();
    // DO WORK
    //myReducer.fileManagerUpdate(my_File_Management);
    //myReducer.reduceWrapper();

    //vector<string> Test_Reduce_Output_Vector = { "(“a”,3)", "(“the”,2)", "(“is”,1)" };
    //my_File_Management.exportReduceFile(Test_Reduce_Output_Vector);
    //@@@@@@@@@@@@@@@@

    return 0;

}