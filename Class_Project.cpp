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

#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT1 8080
#define PORT2 8081
#define BUFFER_SIZE 1024
const char* serverIp = "127.0.0.1";

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
void error(const char* msg);
void communicateWithServer(const char* serverIp, int port, const char* message, bool waitForDone);
//void communicateWithServer(const char* serverIp, int port, const std::vector<std::string>& messages);
void testCommunication(const char* serverIp, int port, const char* message, bool waitForDone, SOCKET connectSocket);


//#################################################################
//#################################################################
//#################################################################

int main()
{
    tic();
    File_Management my_File_Management;
    //Reduce myReducer;

    //my_File_Management.promptUserForDirectories();

    cout << "Start Loading Config File" << endl;
    cout << "=================================================" << endl;
    cout << "LOADING CONFIG FILE" << endl;
    my_File_Management.readConfigFileForDirectories();
    cout << "=================================================" << endl << endl;
    
    int check = workflow(my_File_Management);
    if (check)
    {
        cout << "Failure in workflow.\n";
        return 1;
    }

    cout << "End Program" << endl;
    toc();
}

//#################################################################
//#################################################################
//#################################################################

int workflow(File_Management my_File_Management)
{
    vector<string> inputFiles = my_File_Management.getInputFiles();
    string mapdllPathandName = my_File_Management.getDLLFileLocation();
    const int numOfMapThreads = 17;
    const int numOfReduceThreads = 3;
    mapdllPathandName.append("//mapDLL.dll");

    
    //=============================================================================================
    
    thread mapThreads[numOfMapThreads];

    cout << endl << "Starting Map Section" << endl;
    cout << "=================================================" << endl;


    //SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
    //vector<string> test;

    WSADATA wsaData;
    SOCKET connectSocket = INVALID_SOCKET;
    struct sockaddr_in serverAddr;
    char buffer[BUFFER_SIZE];
    int result;

    // Initialize Winsock
    result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        error("WSAStartup failed");
    }

    // Create socket
    connectSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (connectSocket == INVALID_SOCKET) {
        error("Error creating socket");
    }

    // Setup server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT1);
    inet_pton(AF_INET, serverIp, &serverAddr.sin_addr);

    // Connect to server
    result = connect(connectSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (result == SOCKET_ERROR) {
        error("Connect failed");
    }

    for (int i = 0; i < my_File_Management.getNumberOfInputFiles(); i++)
    {

    //int i = 0;
        //tic();
        my_File_Management.setFileBeingWorked(inputFiles[i]);

        string message = inputFiles[i];
        //test[0] = message;
        if (i == my_File_Management.getNumberOfInputFiles()-1)
        {
            testCommunication(serverIp, PORT1, message.c_str(), true, connectSocket);
            //communicateWithServer(serverIp, PORT1, message.c_str(), true);
        }
        else
        {
            testCommunication(serverIp, PORT1, message.c_str(), false, connectSocket);
            //communicateWithServer(serverIp, PORT1, message.c_str(), false);
        }
        
        //communicateWithServer(serverIp, PORT1, inputFiles);


        /*
        // Map
        Map_Tokenizer mapTokenizerObj(my_File_Management);
        vector<string> fileParsedLineVector = my_File_Management.importMapFile();

        // Create file path/name for saving each intermediate file
        string fileName = my_File_Management.getFileBeingWorked();

        //cout << my_File_Management.getIntermediateFileLocation();

        string interFilePath = my_File_Management.getIntermediateFileLocation();
        interFilePath.append("\\").append("map_").append(fileName);

        // Map
        mapTokenizerObj.runMap(mapdllPathandName, interFilePath, fileParsedLineVector, threadNumber);
        */

        //toc();
    }

    // Cleanup
    closesocket(connectSocket);
    WSACleanup();

    //SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS

    cout << "All Map threads have completed their execution" << endl;
    cout << "=================================================" << endl << endl << endl;



    /*
    //tic();
    // Create multiple threads
    for (int i = 0; i < numOfMapThreads; ++i) {
        cout << "Map Threatz Create: " << i + 1 << std::endl;
        mapThreads[i] = thread(Map_For_Threads, my_File_Management, inputFiles, mapdllPathandName, i);
    }

    // Wait for all threads to finish execution
    for (int i = 0; i < numOfMapThreads; ++i) {
        mapThreads[i].join();
    }

    cout << "All Map threads have completed their execution" << endl;
    cout << "=================================================" << endl << endl << endl;
    */

    //=============================================================================================
    

    cout << "Starting Sort Section" << endl;
    cout << "=================================================" << endl;
    cout << "SORTING FILES" << endl;

    // Sort
    Sort sortObj(my_File_Management, numOfMapThreads, numOfReduceThreads);
    sortObj.runSort();

    cout << "=================================================" << endl << endl << endl;
    

    //=============================================================================================

    cout << "Starting Reduce Section" << endl;
    cout << "=================================================" << endl;

    //WSADATA wsaData;
    connectSocket = INVALID_SOCKET;
    //struct sockaddr_in serverAddr;
    //char buffer[BUFFER_SIZE];
    //int result;

    // Initialize Winsock
    result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        error("WSAStartup failed");
    }

    // Create socket
    connectSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (connectSocket == INVALID_SOCKET) {
        error("Error creating socket");
    }

    // Setup server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT2);
    inet_pton(AF_INET, serverIp, &serverAddr.sin_addr);

    // Connect to server
    result = connect(connectSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (result == SOCKET_ERROR) {
        error("Connect failed");
    }

    for (int i = 0; i < numOfReduceThreads; ++i) {
        string message = to_string(i+1);


        if (i == numOfReduceThreads - 1)
        {
            testCommunication(serverIp, PORT2, message.c_str(), true, connectSocket);
            //communicateWithServer(serverIp, PORT2, message.c_str(), true);
        }
        else
        {
            testCommunication(serverIp, PORT2, message.c_str(), false, connectSocket);
            //communicateWithServer(serverIp, PORT2, message.c_str(), false);
        }
    }

    // Cleanup
    closesocket(connectSocket);
    WSACleanup();

    cout << "All Reduce threads have completed their execution" << endl;
    cout << "=================================================" << endl << endl << endl;
    /*
    thread reduceThreads[numOfReduceThreads];


    cout << "Starting Reduce Section" << endl;
    cout << "=================================================" << endl;

    // Create multiple threads
    for (int i = 0; i < numOfReduceThreads; ++i) {
        cout << "Reduce Threatz Create: " << i + 1 << std::endl;
        reduceThreads[i] = thread(Reduce_For_Threads, my_File_Management, inputFiles, i);
    }

    // Wait for all threads to finish execution
    for (int i = 0; i < numOfReduceThreads; ++i) {
        reduceThreads[i].join();
    }
    
    cout << "All Reduce threads have completed their execution" << endl;
    cout << "=================================================" << endl << endl << endl;
  

    //=============================================================================================
    */

    //master sort
    cout << "Starting Master Sort Section" << endl;
    cout << "=================================================" << endl;
    cout << "SORTING FILES" << endl;
    Sort sortMasterObj(my_File_Management, numOfMapThreads, numOfReduceThreads);
    sortMasterObj.runSortMaster();
    cout << "=================================================" << endl << endl << endl;


    //=============================================================================================
   
    
    //master reduce
    cout << "Starting Master Reduce Section" << endl;
    cout << "=================================================" << endl;
    cout << "REDUCING FILES" << endl;
    Reduce reduceObj(my_File_Management, 0, true);
    reduceObj.reduceCallDLL();
    cout << "=================================================" << endl << endl << endl;
    //toc();
    
    //=============================================================================================
    
    return 0;

}

//#################################################################
//#################################################################
//#################################################################

void Map_For_Threads(File_Management my_File_Management, vector<string> inputFiles, string mapdllPathandName, int threadNumber)
{

    

    //for (int i = 0; i < my_File_Management.getNumberOfInputFiles(); i++)
    //{

        //tic();
        my_File_Management.setFileBeingWorked(inputFiles[threadNumber]);

        // Map
        Map_Tokenizer mapTokenizerObj(my_File_Management);
        vector<string> fileParsedLineVector = my_File_Management.importMapFile();

        // Create file path/name for saving each intermediate file
        string fileName = my_File_Management.getFileBeingWorked();

        //cout << my_File_Management.getIntermediateFileLocation();

        string interFilePath = my_File_Management.getIntermediateFileLocation();
        interFilePath.append("\\").append("map_").append(fileName);

        // Map
        mapTokenizerObj.runMap(mapdllPathandName, interFilePath, fileParsedLineVector, threadNumber);


        //toc();
    //}
}

//#################################################################
//#################################################################
//#################################################################

void Reduce_For_Threads(File_Management my_File_Management, vector<string> inputFiles, int i)
{

    //my_File_Management.setFileBeingWorked(inputFiles[i]);

    //for (int i = 0; i < my_File_Management.getNumberOfInputFiles(); i++)
    //{

    Reduce reduceObj(my_File_Management, i+1, false);
    reduceObj.reduceCallDLL();


    //toc();
//}
}




































void error(const char* msg) {
    std::cerr << msg << " Error Code: " << WSAGetLastError() << std::endl;
    exit(1);
}

void testCommunication(const char* serverIp, int port, const char* message, bool waitForDone, SOCKET connectSocket)
{
    int result;
    char buffer[BUFFER_SIZE];

    // Send message to server
    result = send(connectSocket, message, strlen(message), 0);
    if (result == SOCKET_ERROR) {
        error("Send failed");
    }

    if (waitForDone == false)
    {
        // Receive response from server
        result = recv(connectSocket, buffer, BUFFER_SIZE, 0);
        if (result > 0) {
            buffer[result] = '\0';
            cout << "Incoming from port " << port << ": " << buffer << endl;
        }
        else if (result == 0) {
            cout << "Connection closed by server" << endl;
        }
        else {
            error("Recv failed");
        }
    }



    if (waitForDone) {
        while (true) {
            // Wait for the "Done" message from the server
            result = recv(connectSocket, buffer, BUFFER_SIZE, 0);
            if (result > 0) {
                buffer[result] = '\0';
                cout << "Incoming from port " << port << ": " << buffer << endl;
                if (std::string(buffer) == "Done") {
                    break;
                }
            }
            else if (result == 0) {
                //std::cout << " ########### Connection closed by server" << std::endl;
                //break;
            }
            else {
                error("Recv failed");
            }
        }
    }
}

void communicateWithServer(const char* serverIp, int port, const char* message, bool waitForDone) {
    
    WSADATA wsaData;
    SOCKET connectSocket = INVALID_SOCKET;
    struct sockaddr_in serverAddr;
    char buffer[BUFFER_SIZE];
    int result;

    // Initialize Winsock
    result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        error("WSAStartup failed");
    }

    // Create socket
    connectSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (connectSocket == INVALID_SOCKET) {
        error("Error creating socket");
    }

    // Setup server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    inet_pton(AF_INET, serverIp, &serverAddr.sin_addr);

    // Connect to server
    result = connect(connectSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (result == SOCKET_ERROR) {
        error("Connect failed");
    }


    // Send message to server
    result = send(connectSocket, message, strlen(message), 0);
    if (result == SOCKET_ERROR) {
        error("Send failed");
    }

    if (waitForDone == false)
    {
        // Receive response from server
        result = recv(connectSocket, buffer, BUFFER_SIZE, 0);
        if (result > 0) {
            buffer[result] = '\0';
            std::cout << "Received message from server on port " << port << ": " << buffer << std::endl;
        }
        else if (result == 0) {
            std::cout << "Connection closed by server" << std::endl;
        }
        else {
            error("Recv failed");
        }
    }



    if (waitForDone) {
        while (true) {
            // Wait for the "Done" message from the server
            result = recv(connectSocket, buffer, BUFFER_SIZE, 0);
            if (result > 0) {
                buffer[result] = '\0';
                std::cout << "Received message from server on port " << port << ": " << buffer << std::endl;
                if (std::string(buffer) == "Done") {
                    break;
                }
            }
            else if (result == 0) {
                //std::cout << " ########### Connection closed by server" << std::endl;
                //break;
            }
            else {
                error("Recv failed");
            }
        }
    }

    
    // Cleanup
    closesocket(connectSocket);
    WSACleanup();
    
}





/*
void communicateWithServer(const char* serverIp, int port, const std::vector<std::string>& messages) {
    WSADATA wsaData;
    SOCKET connectSocket = INVALID_SOCKET;
    struct sockaddr_in serverAddr;
    std::string buffer(BUFFER_SIZE, 0);
    int result;

    // Initialize Winsock
    result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        error("WSAStartup failed");
    }

    // Create socket
    connectSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (connectSocket == INVALID_SOCKET) {
        error("Error creating socket");
    }

    // Setup server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    inet_pton(AF_INET, serverIp, &serverAddr.sin_addr);

    // Connect to server
    result = connect(connectSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (result == SOCKET_ERROR) {
        error("Connect failed");
    }

    for (const auto& message : messages) {
        // Send message to server
        result = send(connectSocket, message.c_str(), message.size(), 0);
        if (result == SOCKET_ERROR) {
            error("Send failed");
        }

        // Receive response from server
        int count = 1;
        //while (count < messages.size())
        //{
            result = recv(connectSocket, &buffer[0], BUFFER_SIZE, 0);
            if (result > 0) {
                count++;
                buffer.resize(result);
                std::cout << "Received message from server on port " << port << ": " << buffer << std::endl;
            }
            else if (result == 0) {
                count++;
                std::cout << "Connection closed by server" << std::endl;
                break;
            }
            else {
                count++;
                error("Recv failed");
            }
            buffer.assign(BUFFER_SIZE, 0); // Clear buffer for next message
        //}
    }

    // Cleanup
    closesocket(connectSocket);
    WSACleanup();
}
*/