#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Check for command line args
    if (argc != 2)
    {
        printf("Usage: ./read infile\n");
        return 1;
    }

    // Create buffer to read into
    char buffer[7];

    // Create array to store plate numbers
    char *plates[8];

    // not confirming if file was read correctly or it exists
    // fopen gives the address of the file to read
    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 2;
    }

    int idx = 0;

    // size of char is 1
    // and we are reading 7 of it
    // the function returns the number of items read,
    // which equals number of bytes read when each item is 1 byte
    // if an error occurs, or EOF is reached, the function returns
    // a value smaller than nmemb or even 0
    while (fread(buffer, 1, 7, infile) == 7)
    {

        // Replace '\n' with '\0'
        buffer[6] = '\0';
        // Save plate number in array
        // printf("%p\n", &buffer);
        plates[idx] = malloc(sizeof(char)*7);
        if (plates[idx] == NULL)
        {
            return 3;
        }
        strcpy(plates[idx], buffer);
        idx++;
    }
    // close the file to avoid memory leaks
    fclose(infile);

    for (int i = 0; i < 8; i++)
    {
        printf("%s\n", plates[i]);
        free(plates[i]);
    }
}
