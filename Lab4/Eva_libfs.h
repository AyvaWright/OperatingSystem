
#ifndef EVA_LIBFS_H
#define EVA_LIBFS_H

int fileCreate(const char* filename);
int fileOpen(const char* filename);
int fileWrite(int fd, const char* buffer);
int fileRead(int fd, char* buffer, int size);
int fileClose(int fd);
int fileDelete(const char* filename);

#endif
