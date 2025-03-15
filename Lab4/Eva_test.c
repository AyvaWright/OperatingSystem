#include <stdio.h>
#include <string.h>
#include "Eva_libfs.h"

int test_file_operations(const char* name) {
    char filename[100];
    snprintf(filename, sizeof(filename), "%s_Introduction.txt", name);
    char buffer[1024];
    int fd;

    // Test 1: Create file
    printf("\nTest 1: Creating file '%s'\n", filename);
    if (fileCreate(filename) != 0) {
        printf("Error: Failed to create file\n");
        return -1;
    }
    printf("Success: File created\n");

    // Test 2: Write to file
    printf("\nTest 2: Writing introduction to file\n");
    fd = fileOpen(filename);
    if (fd == -1) {
        printf("Error: Failed to open file for writing\n");
        return -1;
    }

    char intro[1024];
    snprintf(intro, sizeof(intro), 
             "Hello! I am %s, a Computer Science student.\n"
             "I am passionate about programming and system design.\n"
             "I enjoy working on challenging projects that help me\n"
             "learn new concepts and improve my skills.\n", name);

    if (fileWrite(fd, intro) == -1) {
        printf("Error: Failed to write to file\n");
        fileClose(fd);
        return -1;
    }
    fileClose(fd);
    printf("Success: Written introduction to file\n");

    // Test 3: Read from file
    printf("\nTest 3: Reading file contents\n");
    fd = fileOpen(filename);
    if (fd == -1) {
        printf("Error: Failed to open file for reading\n");
        return -1;
    }

    memset(buffer, 0, sizeof(buffer));
    if (fileRead(fd, buffer, sizeof(buffer)) <= 0) {
        printf("Error: Failed to read file\n");
        fileClose(fd);
        return -1;
    }
    fileClose(fd);

    printf("File contents:\n%s\n", buffer);
    printf("Success: Read file contents\n");

    return 0;
}

int main() {
    printf("Starting file system tests...\n");
    
    printf("\n=== Testing for Marius ===\n");
    int result1 = test_file_operations("Marius");
    
    printf("\n=== Testing for Eva ===\n");
    int result2 = test_file_operations("Eva");

    printf("\nCleaning up files...\n");
    if (fileDelete("Marius_Introduction.txt") == 0) {
        printf("Deleted Marius's file\n");
    }
    if (fileDelete("Eva_Introduction.txt") == 0) {
        printf("Deleted Eva's file\n");
    }

    if (result1 == 0 && result2 == 0) {
        printf("\nAll tests completed successfully!\n");
        return 0;
    } else {
        printf("\nSome tests failed!\n");
        return -1;
    }
}