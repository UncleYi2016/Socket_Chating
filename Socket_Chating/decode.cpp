char* decode(char* msg, int n, int N, int d) {
    int e = N - d;
    int i;
    char de[1024]= {'\0'};
    for (i = 0; i < n; i++) {
        if (msg[i] == 0) {
            break;
        }
        if (msg[i] == 127) {
            msg[i] -= 127;
        }
        int j = (int)msg[i] + 127 - i - e;
        if (j >= 127) {
            de[i] = msg[i] - i - e;
        }
        else {
            de[i] = (char)j;
        }
    }
    // de[i] = '\0';
    return de;
}