#include <stdio.h>
#include <stdint.h>
#include <string.h>

// HOW I TESTED
// create text file with some numbers - testfile.txt
//./program testfile.txt binfile2 -TB
//./program binfile2 testfile2.txt -BT
//  check if testfile2.txt is the same

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Invalid arguments.\n");
        return 1;
    }

    int mode;
    if (strcmp(argv[3], "-BT") == 0)
    {
        mode = 1;
    }
    else if (strcmp(argv[3], "-TB") == 0)
    {
        mode = 2;
    }

    if (mode == 1)
    {
        char i_filename[100], o_filename[100];
        strcpy(i_filename, argv[1]);
        strcpy(o_filename, argv[2]);

        FILE *iFP = fopen(i_filename, "rb");
        FILE *oFP = fopen(o_filename, "w");

        if (!iFP)
        {
            perror("Could not open file");
            return 1;
        }

        uint16_t buff;
        while (fread(&buff, sizeof(uint16_t), 1, iFP))
        {
            fprintf(oFP, "%d\n", buff);
        }

        fclose(iFP);
        fclose(oFP);
    }
    else if (mode == 2)
    {
        char i_filename[100], o_filename[100];
        strcpy(i_filename, argv[1]);
        strcpy(o_filename, argv[2]);

        FILE *iFP = fopen(i_filename, "r");
        FILE *oFP = fopen(o_filename, "wb");

        if (!iFP)
        {
            perror("Could not open file");
            return 1;
        }

        uint16_t buff_num;
        char buff_s[10];
        while (fscanf(iFP, "%d", &buff_num) != EOF)
        {
            fwrite(&buff_num, sizeof(uint16_t), 1, oFP);
        }

        fclose(iFP);
        fclose(oFP);
    }

    return 0;
}