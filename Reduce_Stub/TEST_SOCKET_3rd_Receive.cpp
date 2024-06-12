// server2.cpp
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
//#include "Map_Tokenizer.h"
#include "File_Management.h"
#include "Reduce.h"
#include <string>
#include <thread>

#pragma comment(lib, "ws2_32.lib")

#define PORT2 8081
#define BUFFER_SIZE 1024

void Reduce_For_Threads(File_Management my_File_Management, int i, SOCKET clientSocket);

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
        serverAddr.sin_port = htons(PORT2);
        result = bind(listenSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
        if (result == SOCKET_ERROR) {
            error("Bind failed");
        }

        // Listen for incoming connections
        result = listen(listenSocket, SOMAXCONN);
        if (result == SOCKET_ERROR) {
            error("Listen failed");
        }

        cout << "Reduce Stub listening on port " << PORT2 << endl;
        cout << "============================================================================" << endl << endl;


        //########################################################################################################
        File_Management my_File_Management;
        my_File_Management.readConfigFileForDirectories();
        string mapdllPathandName = my_File_Management.getDLLFileLocation();
        int count = 0;
        thread reduceThreads[3];

        // Accept a client socket
        clientSocket = accept(listenSocket, (struct sockaddr*)&clientAddr, &clientAddrSize);
        if (clientSocket == INVALID_SOCKET) {
            error("Accept failed");
        }

        while (true) {


            // Receive message from client
            result = recv(clientSocket, &buffer[0], BUFFER_SIZE, 0);
            if (result > 0) {
                buffer.resize(result);

                //###########################################################################################
                // Do Stuff

                buffer.resize(result);

                //string mapdllPathandName = "C:\\Users\\tpesp\\source\\repos\\CSE-687-Object-Oriented-Design-Project-1";
                //cout << "Reduce Threatz Create: " << count + 1 << std::endl;
                reduceThreads[count] = thread(Reduce_For_Threads, my_File_Management, count, clientSocket);
                //mapThreads.join();
                //mapThreads[count].detach();
                count++;

                //std::cout << "Server2 received message: " << buffer << std::endl;

                /*
                // Send response to client
                const char* response = "Hello from Server2!";
                result = send(clientSocket, response, strlen(response), 0);
                if (result == SOCKET_ERROR) {
                    error("Send failed");
                }
                */


                if (count == 3) {

                    // Wait for all threads to finish execution
                    for (int i = 0; i < count; ++i) {
                        reduceThreads[i].join();
                    }

                    // Simulate some processing delay
                    //this_thread::sleep_for(chrono::seconds(5));

                    // Send "Done" message to client
                    const char* doneMessage = "Done";
                    result = send(clientSocket, doneMessage, strlen(doneMessage), 0);
                    if (result == SOCKET_ERROR) {
                        error("Send failed");
                    }
                }

            }
            else if (result == 0) {
                cout << "Connection closing..." << endl;
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













































void Reduce_For_Threads(File_Management my_File_Management, int i, SOCKET clientSocket)
{

    // Send a message to the client
    string outGoingMessage = "";
    outGoingMessage.append("Start Reducing Files Numbered: ").append(my_File_Management.getFileBeingWorked());
    const char* response = "Reduce operation Started!";
    int result = send(clientSocket, outGoingMessage.c_str(), strlen(outGoingMessage.c_str()), 0);
    if (result == SOCKET_ERROR) {
        error("Send failed");
    }

    //my_File_Management.setFileBeingWorked(inputFiles[i]);

    //for (int i = 0; i < my_File_Management.getNumberOfInputFiles(); i++)
    //{

    cout << "Thread created to reduce files numbered: " << i+1 << endl;

    Reduce reduceObj(my_File_Management, i + 1, false);
    reduceObj.reduceCallDLL();

    // Send a message to the client
    outGoingMessage = "";
    outGoingMessage.append("Finished Reducing Files Numbered: ").append(my_File_Management.getFileBeingWorked());
    const char* response2 = "Reduce operation completed!";
    result = send(clientSocket, outGoingMessage.c_str(), strlen(outGoingMessage.c_str()), 0);
    if (result == SOCKET_ERROR) {
        error("Send failed");
    }

    //toc();
//}
}