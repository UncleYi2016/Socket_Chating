#include <stdio.h>
#include <math.h>
char* encrypt(char* msg, int n, int N, int e) {
    int i;
    char en[1024] = { '\0' };
    for (i = 0; i < n; i++) {
        if (msg[i] == 0) {
            break;
        }
        en[i] = (msg[i] + i + e) % 127;
        if (en[i] == 0) {
            en[i] = 127;
        }
    }
    // en[i] = '\0';
    return en;
}