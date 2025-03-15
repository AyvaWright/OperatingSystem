
#include "Eva_libfs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int fileCreate(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) return -1;
    fclose(file);
    return 0;
}

int fileOpen(const char* filename) {
    FILE* file = fopen(filename, "r+");
    if (file == NULL) return -1;
    int fd = fileno(file);
    return fd;
}

int fileWrite(int fd, const char* buffer) {
    FILE* file = fdopen(fd, "w");
    if (file == NULL) return -1;
    int result = fputs(buffer, file);
    fflush(file);
    return result;
}

int fileRead(int fd, char* buffer, int size) {
    FILE* file = fdopen(fd, "r");
    if (file == NULL) return -1;
    return fread(buffer, 1, size, file);
}

int fileClose(int fd) {
    FILE* file = fdopen(fd, "r");
    if (file == NULL) return -1;
    return fclose(file);
}

int fileDelete(const char* filename) {
    return remove(filename);
}
