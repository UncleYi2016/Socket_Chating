#include "stdafx.h"
#include "save_log.h"

extern vector<struct sock_key> clientVec;
void receive_thread(void *dummy) {
    SOCKET clientSock = (SOCKET)dummy;
    int key_len = 0;
    char keyN[5];
    char keyD[5];
    struct sock_key thisSock;
    key_len = recv(clientSock, keyN, sizeof(keyN), 0);
    if (key_len == SOCKET_ERROR) {
        cout << "sock recv() fail with " << WSAGetLastError() << endl;
        closesocket(clientSock);
        return;
    }
    key_len = recv(clientSock, keyD, sizeof(keyD), 0);
    if (key_len == SOCKET_ERROR) {
        cout << "sock recv() fail with " << WSAGetLastError() << endl;
        closesocket(clientSock);
        return;
    }
    thisSock.sock = clientSock;
    thisSock.keyN = atoi(keyN);
    thisSock.keyD = atoi(keyD);
    clientVec.push_back(thisSock);
    // connection established.
    while (1) {
        time_t timep;
        time(&timep);
        int msg_len = 0;
        char msg[1024] = { '\0' };
        char log[1500] = { '\0' };
        char en_msg[1024] = { '\0' };
        msg_len = recv(clientSock, msg, sizeof(msg), 0);
        if (msg_len == SOCKET_ERROR) {
            cout << "sock recv() fail with " << WSAGetLastError() << endl;
            closesocket(clientSock);
            return;
        }
        cout << msg << endl;
        strcpy(msg, decode(msg, sizeof(msg), thisSock.keyN, thisSock.keyD));
        
        strcpy(log, asctime(gmtime(&timep)));
        log[strlen(log) - 1] = ' ';
        strcat(log, msg);
        strcat(log, "\n");
        save_log(log);
        for (int i = 0; i < clientVec.size(); i++) {
            if (clientVec[i].sock != clientSock) {
                strcpy(en_msg, encrypt(msg, sizeof(msg), clientVec[i].keyN, clientVec[i].keyD));
                if (send(clientVec[i].sock, en_msg, sizeof(en_msg), 0) == SOCKET_ERROR) {
                    closesocket(clientVec[i].sock);
                    clientVec.erase(clientVec.begin() + i);
                }
            }
        }
    }
}