#include "stdafx.h"
extern int n, e, d;
void receive_thread(void* dummy) {
    SOCKET connectSock = (SOCKET)dummy;

    while (1) {
        int msg_len = 0;
        char msg[1024] = { '\0' };
        msg_len = recv(connectSock, msg, sizeof(msg), 0);
        if (msg_len == SOCKET_ERROR) {
            cout << "sock recv() fail with " << WSAGetLastError() << endl;
            closesocket(connectSock);
            return;
        }
        strcpy(msg, decode(msg, sizeof(msg), n, e));
        cout << msg << endl;
    }
}