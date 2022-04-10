#include <stdio.h> //ONLY USED FOR BUFSIZ MACRO
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

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
            write(STDOUT_FILENO, "\n==>", 4);
            write(STDOUT_FILENO, argv[i], strlen(argv[i]));
            write(STDOUT_FILENO, "<==\n", 4);

            int fd = open(argv[i], O_RDONLY);
            if (fd == -1)
            {
                perror("Error opening file");
                return 1;
            }

            char buffer[BUFSIZ];
            ssize_t bytes;

            int newline_cnt = 0;
            int bytes_to_print = 0;
            while ((bytes = read(fd, buffer, BUFSIZ)) > 0)
            {
                for (int i = 0; i < bytes && newline_cnt < 10; i++, bytes_to_print++)
                {
                    if (buffer[i] == '\n')
                    {
                        newline_cnt++;
                    }
                }

                write(STDOUT_FILENO, buffer, bytes_to_print);
            }

            close(fd);
        }
    }

    return 0;
}