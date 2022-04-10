#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

#define PROCESS_NUM 10

int main(int argc, char* argv[]) {

    for (int i = 0; i < PROCESS_NUM; i++) {
        int pid = fork();
        if (pid == -1) {
            printf("Error with creating process\n");
            return 2;
        }
        if (pid == 0) {
            // Child process
  
            break;
        }
    }



    for (int i = 0; i < PROCESS_NUM; i++) {
        wait(NULL);
    }
    return 0;
}