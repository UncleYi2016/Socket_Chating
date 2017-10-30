#pragma once
#include "WinSock2.h"
struct sock_key {
    SOCKET sock;
    short keyN;
    short keyD;
};
