
#include "Reduce.h"
#include "File_Management.h"
#include "framework.h"

Reduce::Reduce() {
    //do nothing
}

Reduce::Reduce(File_Management files, int partNum, bool isMasterInput) {
    fileManagerUpdate(files);
    partNumber = partNum;
    isMaster = isMasterInput;
}

int Reduce::fileManagerUpdate(File_Management newFileManeger) {
    fileManager = newFileManeger;

    return 0;
}

typedef int (*ReduceDLLFunc)(File_Management, string, bool);

int Reduce::reduceCallDLL() {
    string filepathToDLL;
    vector<string> DllFilesToSearch = fileManager.getDllFiles();
    for (int i = 0; i < DllFilesToSearch.size(); i++)    {
        //cout << "\nDllFilesToSearch: " << DllFilesToSearch[i] << "finding reduce HERE: "<< DllFilesToSearch[i].find("Reduce");
        if (DllFilesToSearch[i].find("Reduce") > 0 && DllFilesToSearch[i].find("Reduce") < DllFilesToSearch[i].length()) {
            filepathToDLL = DllFilesToSearch[i];
        }
    }

    wstring temp = wstring(filepathToDLL.begin(), filepathToDLL.end());
    LPCWSTR dummy = temp.c_str();

    HINSTANCE hDLL = LoadLibrary(dummy);

    if (hDLL != NULL) {
        // Get pointer to the wrapper function
        ReduceDLLFunc reduceWrapperFunc = (ReduceDLLFunc)GetProcAddress(hDLL, "reduceWrapper");
        if (reduceWrapperFunc != NULL) {
            // Call the wrapper function
            string partNumAsString = to_string(partNumber);
            int didReduceSuccessed = reduceWrapperFunc(fileManager, partNumAsString, isMaster);
        }
        else {
            std::cerr << "Failed to get function pointer." << std::endl;
            cout << GetLastError();
        }
        // Free the DLL
        FreeLibrary(hDLL);
    }
    else {
        std::cerr << "Failed to load DLL." << std::endl;
    }

    return 0;
}
