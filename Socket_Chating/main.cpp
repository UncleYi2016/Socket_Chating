// main.cpp : 定义控制台应用程序的入口点。
//
#pragma comment (lib, "ws2_32.lib")
#include "stdafx.h"
#include "save_log.h"

// Global variables.
vector<struct sock_key> clientVec;

using namespace std;
int main()
{
    char serverIp[20];
    WSADATA wsaData;
    struct sockaddr_in local, clientIn;
    SOCKET sock, clientSock;
    
    save_log("**************************************Server Started**************************************\n");
    if (WSAStartup(0x202, &wsaData) == SOCKET_ERROR) {
        cout << "WSAStartup() failed with " << WSAGetLastError() << endl;
        WSACleanup();
        return ERROR_EXIT;
    }

    local.sin_family = AF_INET;
    local.sin_addr.s_addr = INADDR_ANY;
    local.sin_port = htons(PORT);
    

    // local socket intialization.
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        cout << "local socket intializing failed with " << WSAGetLastError() << endl;
        WSACleanup();
        return ERROR_EXIT;
    }

    // client bind for server.
    if (::bind(sock, (struct sockaddr *)&local, sizeof(local)) == SOCKET_ERROR) {
        cout << "sock bind() failed with " << WSAGetLastError() << endl;
        WSACleanup();
        return ERROR_EXIT;
    }

    // client listen for server
    if (listen(sock, QUEUE_LENGTH) == SOCKET_ERROR) {
        cout << "sock listen() failed with " << WSAGetLastError() << endl;
        WSACleanup();
        return ERROR_EXIT;
    }

    // client accept for server
    while (1) {
        int addrLen = sizeof(clientIn);
        clientSock = accept(sock, (struct sockaddr *)&clientIn, &addrLen);
        if (clientSock == SOCKET_ERROR) {
            cout << "sock accept() failed with " << WSAGetLastError();
            WSACleanup();
            return ERROR_EXIT;
        }
        _beginthread(receive_thread, 0, (void*)clientSock);
    }
    save_log("**************************************Server Ended**************************************\n");
    return NORMALLY_EXIT;
    
}






