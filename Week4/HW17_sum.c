#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

void printd(int output_fd, int n) {
    if(n < 0)
    {
        write(output_fd, "-", 1);
        printd(output_fd, -n);
        return;
    }
    else if(n == 0)
    {
        return;
    }
    else
    {
        printd(output_fd, n / 10);
    }

    char lastDigit = n % 10 + '0';
    write(output_fd, &lastDigit, 1);
}

int main(int argc, char *argv[])
{
    int fd[2];
    pipe(fd);
    int pid = fork();

    if(pid == -1)
    {
        perror("");
        return 1;
    }
    else if(pid == 0)
    {
        close(fd[0]);
        int sum =0;
        for(int i =1; i <argc/2; i++)
        {
            sum += atoi(argv[i]);
        }

        printd(fd[1], sum);

        close(fd[1]);
    }
    else
    {
        close(fd[1]);
        int sum =0;
        for(int i =argc/2; i <argc; i++)
        {
            sum += atoi(argv[i]);
        }

        wait(NULL);

        char buffer[50];
        read(fd[0],buffer,50);

        sum += atoi(buffer);
        printf("%d\n", sum);

        close(fd[0]);
    }

    return 0;
}