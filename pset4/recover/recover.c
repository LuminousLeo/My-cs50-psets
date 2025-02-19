#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//8 bits or 1 byte of memory
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //check for proper usage
    if (argc != 2)
    {
        printf("Usage: forensic.raw\n");
        return 1;
    }

    char *infile = argv[1];
    char outfile[8];    //000.jpg/0
    int file_number = 0;
    FILE *inptr = fopen(infile, "r");
    FILE *outptr = NULL;

    //some error checking
    if (inptr == NULL)
    {
        printf("Could not open %s\n", infile);
        return 1;
    }

    const int block_size = 512; //set block size
    BYTE buffer[block_size]; //creation of a buffer

    //check for 512 bytes of memory
    while (fread(buffer, 1, block_size, inptr) == block_size)
    {
        //if it is a jpeg
        if (buffer[0] == 0xFF && buffer[1] == 0xD8 && buffer[2] == 0xFF && (buffer[3] & 0xF0) == 0xE0)
        {
            //close the previous jpeg file
            if (outptr != NULL)
            {
                fclose(outptr);
            }

            //number the jpeg files
            sprintf(outfile, "%03i.jpg", file_number);
            outptr = fopen(outfile, "w");
            file_number++;
        }

        //if jpeg file exists, write in it
        if (outptr != NULL)
        {
            fwrite(buffer, 1, block_size, outptr);
        }
    }

    //close opened files
    fclose(outptr);
    fclose(inptr);

    return 0;
}