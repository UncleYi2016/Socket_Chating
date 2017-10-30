// Client.cpp : 定义控制台应用程序的入口点。
//
#pragma comment (lib, "ws2_32.lib")
#include "stdafx.h"
int n, e, d;

int main()
{
    struct sockaddr_in serverAddr;
    struct hostent *hp;
    SOCKET connectSock;
    WSADATA wsaData;

    char serverName[30];
    unsigned int serverIp;
    
    gets_s(serverName, sizeof(serverName));

    if (WSAStartup(0x202, &wsaData) == SOCKET_ERROR) {
        cout << "WSAStartup() failed with " << WSAGetLastError() << endl;
        WSACleanup();
        return ERROR_EXIT;
    }

    if (isalpha(serverName[0])) {
        hp = gethostbyname(serverName);
    }
    else {
        serverIp = inet_addr(serverName);
        hp = gethostbyaddr((char*)&serverIp, 4, AF_INET);
    }

    if (hp == NULL) {
        cout << "Cannot resolve address: " << WSAGetLastError();
        WSACleanup();
        return ERROR_EXIT;
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    memcpy(&(serverAddr.sin_addr), hp->h_addr, hp->h_length);
    serverAddr.sin_family = hp->h_addrtype;
    serverAddr.sin_port = htons(PORT);

    connectSock = socket(AF_INET, SOCK_STREAM, 0);

    if (connectSock == INVALID_SOCKET) {
        cout << "socket intialized failed." << endl;
        WSACleanup();
        return ERROR_EXIT;
    }

    cout << "Client connecting to: " << hp->h_name << endl;

    if (connect(connectSock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cout << "socket connect() failed with " << WSAGetLastError << endl;
        WSACleanup();
        return ERROR_EXIT;
    }

    _beginthread(receive_thread, 0, (void*)connectSock);
    send_thread((void*) connectSock);
}

