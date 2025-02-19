#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        printf("Usage: input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    char *infile = argv[1];
    FILE *inptr = fopen(infile, "r");

    if (inptr == NULL)
    {
        printf("Error opening the input file\n");
        return 1;
    }

    // Read header
    // TODO #3
    WAVHEADER header;
    fread(&header, sizeof(WAVHEADER), 1, inptr);

    // Use check_format to ensure WAV format
    // TODO #4
    if (check_format(header) != 1)
    {
        printf("The input is not a wav file");
        return 1;
    }

    // Open output file for writing
    // TODO #5
    char *outfile = argv[2];
    FILE *outptr = fopen(outfile, "w");

    if (outptr == NULL)
    {
        printf("Error creating the output file\n");
        return 1;
    }

    // Write header to file
    // TODO #6
    fwrite(&header, sizeof(WAVHEADER), 1, outptr);

    // Use get_block_size to calculate size of block
    // TODO #7
    int block_size = get_block_size(header);

    // Write reversed audio to file
    // TODO #8
    int buffer[block_size];

    //set file pointer to the end of the file
    fseek(inptr, block_size, SEEK_END);

    //while the pointer is not pointing to the end of wave header
    while (ftell(inptr) - block_size > sizeof(header))
    {
        //set pointer to where i'm reading and move backwards
        fseek(inptr, -2 * block_size, SEEK_CUR);

        fread(buffer, block_size, 1, inptr);
        fwrite(buffer, block_size, 1, outptr);
    }

    fclose(inptr);
    fclose(outptr);
}

int check_format(WAVHEADER header)
{
    // TODO #4
    //if it is a wave file return true
    if (header.format[0] == 'W' && header.format[1] == 'A' && header.format[2] == 'V' && header.format[3] == 'E')
    {
        return 1;
    }

    return 0;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    const int byte_in_bit = 8;
    int block_size = header.numChannels * (header.bitsPerSample / byte_in_bit);

    return block_size;
}