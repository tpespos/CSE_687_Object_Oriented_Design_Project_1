// server1.cpp
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "Map_Tokenizer.h"
#include "File_Management.h"
#include <string>
#include <thread>

#pragma comment(lib, "ws2_32.lib")

#define PORT1 8080
#define BUFFER_SIZE 1024

void Map_For_Threads(File_Management my_File_Management, string message, string mapdllPathandName, int threadNumber, SOCKET clientSocket);
void communicateWithServer(const char* serverIp, int port, const char* message);

void error(const char* msg) {
    std::cerr << msg << " Error Code: " << WSAGetLastError() << std::endl;
    exit(1);
}

int main() {

    while (true)
    {
        WSADATA wsaData;
        SOCKET listenSocket = INVALID_SOCKET, clientSocket = INVALID_SOCKET;
        struct sockaddr_in serverAddr, clientAddr;
        int clientAddrSize = sizeof(clientAddr);
        std::string buffer(BUFFER_SIZE, 0);
        int result;

        // Initialize Winsock
        result = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (result != 0) {
            error("WSAStartup failed");
        }

        // Create socket
        listenSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (listenSocket == INVALID_SOCKET) {
            error("Error creating socket");
        }

        // Bind socket
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = INADDR_ANY;
        serverAddr.sin_port = htons(PORT1);
        result = bind(listenSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
        if (result == SOCKET_ERROR) {
            error("Bind failed");
        }

        // Listen for incoming connections
        result = listen(listenSocket, SOMAXCONN);
        if (result == SOCKET_ERROR) {
            error("Listen failed");
        }

        cout << "Map Stub listening on port " << PORT1 << endl;
        cout << "============================================================================" << endl << endl;

        //########################################################################################
        File_Management my_File_Management;
        my_File_Management.readConfigFileForDirectories();
        string mapdllPathandName = my_File_Management.getDLLFileLocation();
        int count = 0;
        thread mapThreads[17];

        // Accept a client socket
        clientSocket = accept(listenSocket, (struct sockaddr*)&clientAddr, &clientAddrSize);
        if (clientSocket == INVALID_SOCKET) {
            error("Accept failed");
        }

        while (true) {


            // Receive message from client
            result = recv(clientSocket, &buffer[0], BUFFER_SIZE, 0);
            if (result > 0) {
                //###########################################################################################
                // Do Stuff

                buffer.resize(result);

                //string mapdllPathandName = "C:\\Users\\tpesp\\source\\repos\\CSE-687-Object-Oriented-Design-Project-1";
                //cout << "Map Threatz Create: " << count + 1 << std::endl;
                mapThreads[count] = thread(Map_For_Threads, my_File_Management, buffer, mapdllPathandName, count, clientSocket);
                //mapThreads.join();
                //mapThreads[count].detach();
                count++;

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




                //buffer[result] = '\0';
                //std::cout << "Server1 received message: " << buffer << std::endl;





                //###########################################################################################
                // respond to stuff

                // Send response to client


                /*
                const char* response = "Hello from Server1!";
                result = send(clientSocket, response, strlen(response), 0);
                if (result == SOCKET_ERROR) {
                    error("Send failed");
                }
                */




                if (count == 17) {

                    // Wait for all threads to finish execution
                    for (int i = 0; i < count; ++i) {
                        mapThreads[i].join();
                    }

                    // Simulate some processing delay
                    //std::this_thread::sleep_for(std::chrono::seconds(5));

                    // Send "Done" message to client
                    const char* doneMessage = "Done";
                    result = send(clientSocket, doneMessage, strlen(doneMessage), 0);
                    if (result == SOCKET_ERROR) {
                        error("Send failed");
                    }
                }



            }
            else if (result == 0) {
                std::cout << "Connection closing..." << std::endl;
                break;
            }
            else {
                error("Recv failed");
            }

            // Close client socket
            //closesocket(clientSocket);
            buffer.assign(BUFFER_SIZE, 0);
        }

        // Cleanup
        closesocket(listenSocket);
        WSACleanup();
    }
    return 0;
}




















void Map_For_Threads(File_Management my_File_Management, string message, string mapdllPathandName, int threadNumber, SOCKET clientSocket)
{
    
    my_File_Management.setFileBeingWorked(message);
    string outGoingMessage = "";
    outGoingMessage.append("Start Maping File: ").append(my_File_Management.getFileBeingWorked());
    // Send a message to the client
    const char* response = "Map operation Started!";
    int result = send(clientSocket, outGoingMessage.c_str(), strlen(outGoingMessage.c_str()), 0);
    if (result == SOCKET_ERROR) {
        error("Send failed");
    }
    

    cout << "Thread created to Map the file: " << my_File_Management.getFileBeingWorked() << endl;

    // Map
    Map_Tokenizer mapTokenizerObj(my_File_Management);
    vector<string> fileParsedLineVector = my_File_Management.importMapFile();

    // Create file path/name for saving each intermediate file
    string fileName = my_File_Management.getFileBeingWorked();

    //cout << my_File_Management.getIntermediateFileLocation();

    string interFilePath = my_File_Management.getIntermediateFileLocation();
    //string interFilePath = "C:\\Users\\tpesp\\source\\repos\\CSE-687-Object-Oriented-Design-Project-1\\Plays\\interm";
    interFilePath.append("\\").append("map_").append(fileName);

    // Map
    mapTokenizerObj.runMap(mapdllPathandName, interFilePath, fileParsedLineVector, threadNumber);

    
    // Send a message to the client
    outGoingMessage = "";
    outGoingMessage.append("Finished Maping File: ").append(my_File_Management.getFileBeingWorked());
    const char* response2 = "Map Operation completed!";
    result = send(clientSocket, outGoingMessage.c_str(), strlen(outGoingMessage.c_str()), 0);
    if (result == SOCKET_ERROR) {
        error("Send failed");
    }
    
}























/*

void communicateWithServer(const char* serverIp, int port, const char* message) {
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

    // Cleanup
    closesocket(connectSocket);
    WSACleanup();
}
*/