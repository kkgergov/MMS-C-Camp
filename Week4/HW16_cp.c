#include <stdio.h> //ONLY USED FOR BUFSIZ MACRO
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc <= 2)
    {
        write(STDOUT_FILENO, "missing source or destination\n", 30);
    }
    else
    {
        int fd1 = open(argv[1], O_RDONLY);
        if(fd1 == -1)
        {
            perror("error opening source");
            return 1;
        }
        int fd2 = open(argv[2], O_CREAT | O_RDWR | O_TRUNC, 0666);
        if(fd2 == -1)
        {
            perror("error opening destination");
            return 1;
        }

        ssize_t bytes;
        char buffer[BUFSIZ];
        while((bytes = read(fd1, buffer, BUFSIZ)) > 0)
        {
            write(fd2, buffer, bytes);
        }

        close(fd1);
        close(fd2);
    }

    return 0;
}