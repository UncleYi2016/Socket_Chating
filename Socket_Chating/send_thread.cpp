#include "stdafx.h"

extern int n, e, d;
void send_thread(void *dummy) {
    SOCKET connectSock = (SOCKET)dummy;
    char name[20];
    char keyN[5];
    char keyE[5];
    char keyD[5];
    int key_len = 0;

    srand((unsigned)time(NULL));
    e = rand() % 50;
    d = rand() % 50;
    n = e + d;
    itoa(n, keyN, 10);
    itoa(e, keyE, 10);
    itoa(d, keyD, 10);

    key_len = send(connectSock, keyN, sizeof(keyN), 0);
    if (key_len == SOCKET_ERROR) {
        fprintf(stderr, "send() failed with error %d\n", WSAGetLastError());
        WSACleanup();
        return;
    }

    key_len = send(connectSock, keyD, sizeof(keyD), 0);
    if (key_len == SOCKET_ERROR) {
        fprintf(stderr, "send() failed with error %d\n", WSAGetLastError());
        WSACleanup();
        return;
    }

    cout << "Please enter your name (up to 20 characters): ";
    gets_s(name, sizeof(name));

    while (1) {
        char content[1004];
        char msg[1024] = { '\0' };
        int msg_len;
        int exit = 0;

        cout << name << ": ";

        gets_s(content, sizeof(content));

        sprintf(msg, "%s", name);
        strcat(msg, ": ");
        strcat(msg, content);
        if (strcmp(content, "Bye") == 0) {
            cout << "Bye" << endl;
            exit = 1;
        }
        strcpy(msg, encrypt(msg, sizeof(msg), n, e));

        msg_len = send(connectSock, msg, sizeof(msg), 0);
        if (msg_len == SOCKET_ERROR) {
            fprintf(stderr, "send() failed with error %d\n", WSAGetLastError());
            WSACleanup();
            return;
        }
        if (exit) {
            cout << "Client exited." << endl;
            WSACleanup();
            return;
        }
    }
}