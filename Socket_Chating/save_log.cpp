#include <stdio.h>
#include <string.h>
#include <io.h>

void save_log(char* msg) {
    FILE *log_file = fopen("msg_log.log", "a+");
    if (log_file == NULL) {
        printf("Log file open failed.\n");
        return;
    }
    fseek(log_file, 0L, SEEK_END);
    int a = fwrite(msg, sizeof(char), strlen(msg), log_file);
    fclose(log_file);
}