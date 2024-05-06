#include "Reduce.h"
#include "File_Management.h"
#include "framework.h"


Reduce::Reduce() {
    //do nothing
}


Reduce::Reduce(File_Management files) {
    fileManagerUpdate(files);

}

int Reduce::fileManagerUpdate(File_Management newFileManeger) {
    fileManager = newFileManeger;

    return 0;
}

typedef int (*ReduceDLLFunc)(File_Management);

int Reduce::reduceCallDLL() {
    string filepathToDLL;
    vector<string> DllFilesToSearch = fileManager.getDllFiles();
    for (int i = 0; i < DllFilesToSearch.size(); i++)    {
        cout << "\nDllFilesToSearch: " << DllFilesToSearch[i] << "finding reduce HERE: "<< DllFilesToSearch[i].find("Reduce");
        if (DllFilesToSearch[i].find("Reduce") > 0 && DllFilesToSearch[i].find("Reduce") < DllFilesToSearch[i].length()) {
            filepathToDLL = DllFilesToSearch[i];
        }
    }
    cout << "\ndllFileName: " << filepathToDLL;
    
    //filepathToDLL = DllFilesToSearch[1];

    //string filepathToDLLs = "C:\\Users\\lande\\source\\repos\\tpespos\\CSE_687_Object_Oriented_Design_Project_1\\x64\\Debug\\ReduceDLL.dll";

    wstring temp = wstring(filepathToDLL.begin(), filepathToDLL.end());
    LPCWSTR dummy = temp.c_str();

    HINSTANCE hDLL = LoadLibrary(dummy);

    if (hDLL != NULL) {
        // Get pointer to the wrapper function
        ReduceDLLFunc reduceWrapperFunc = (ReduceDLLFunc)GetProcAddress(hDLL, "reduceWrapper");
        if (reduceWrapperFunc != NULL) {
            // Call the wrapper function
            int didReduceSuccessed = reduceWrapperFunc(fileManager);
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


