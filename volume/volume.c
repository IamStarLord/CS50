// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 2;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 2;
    }

    float factor =atof(argv[3]);

    // TODO: Copy header from input file to output file
    // variable to store header
    // likely malloc should be used here
    uint8_t header[HEADER_SIZE];

    // fread from the file the header
    int ret = fread(&header, sizeof(uint8_t), HEADER_SIZE, input);
    // check if it is stored correctly
    if (ret != HEADER_SIZE)
    {
        printf("Could not read file header.\n");
        return 3;
    }
    // write header into the output.wav file
    ret = fwrite(&header, sizeof(uint8_t), HEADER_SIZE, output);
    if (ret != HEADER_SIZE)
    {
        printf("Could not write file header.\n");
        return 4;
    }


    // TODO: Read samples from input file and write updated data to output file
    // read one sample at a time
    int16_t sample;

    while(fread(&sample, sizeof(int16_t), 1, input) == 1)
    {
        sample = sample * factor;
        // write sample into the outfile
        if (fwrite(&sample, sizeof(int16_t), 1, output) != 1)
        {
            printf("Could not write to file.\n");
            return 5;
        }

    }

    // Close files
    fclose(input);
    fclose(output);
}
