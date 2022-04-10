#include <stdio.h> //ONLY USED FOR BUFSIZ MACRO
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        char buffer[BUFSIZ];
        ssize_t bytes;

        while ((bytes = read(STDIN_FILENO, buffer, BUFSIZ)) > 0)
        {
            write(STDOUT_FILENO, buffer, bytes);
        }
    }
    else
    {
        for (int i = 1; i < argc; i++)
        {
            int fd = open(argv[i], O_RDONLY);
            if (fd == -1)
            {
                perror("Error opening file");
                return 1;
            }

            char buffer[BUFSIZ];
            ssize_t bytes;

            while ((bytes = read(fd, buffer, BUFSIZ)) > 0)
            {
                write(STDOUT_FILENO, buffer, bytes);
            }

            close(fd);
        }
    }

    return 0;
}