
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

void execute_command(const char *cmd, char *const args[]) {
    if (execvp(cmd, args) == -1) {
        perror("execvp failed");
        exit(EXIT_FAILURE);
    }
}

int main() {
    pid_t pid;
    int status;
    int num_children = 10;

    // Commands for child processes
    char *commands[][4] = {
        {"echo", "Hello Eva", NULL},
        {"ls", "-l", NULL},
        {"pwd", NULL},
        {"date", NULL},
        {"whoami", NULL},
        {"ps", "aux", NULL},
        {"cat", "/etc/hostname", NULL},
        {"uname", "-a", NULL},
        {"df", "-h", NULL},
        {"free", "-h", NULL}
    };

    printf("Parent process (PID: %d) starting...\n", getpid());

    // Create multiple child processes
    for (int i = 0; i < num_children; i++) {
        pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } 
        else if (pid == 0) {
            // Child process
            printf("Child process %d (PID: %d) executing: %s\n", 
                   i + 1, getpid(), commands[i][0]);
            execute_command(commands[i][0], commands[i]);
            exit(EXIT_SUCCESS);
        }
    }

    // Parent process waits for all children
    for (int i = 0; i < num_children; i++) {
        pid_t terminated_pid = wait(&status);
        
        if (WIFEXITED(status)) {
            printf("Child process (PID: %d) exited normally with status: %d\n", 
                   terminated_pid, WEXITSTATUS(status));
        } 
        else if (WIFSIGNALED(status)) {
            printf("Child process (PID: %d) terminated by signal: %d\n", 
                   terminated_pid, WTERMSIG(status));
        }
    }

    printf("Parent process completed. All child processes finished.\n");
    return 0;
}
