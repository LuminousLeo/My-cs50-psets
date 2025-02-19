#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Change all black pixels to a color of your choosing

    for (int i = 0; i < height; i++)    //column
    {
        for (int j = 0; j < width; j++) //row
        {

            if (image[i][j].rgbtBlue == 0x0 && image[i][j].rgbtGreen == 0x0 && image[i][j].rgbtRed == 0x0)  //check if black
            {
                //change it to yellow
                image[i][j].rgbtRed = 0xFF;
                image[i][j].rgbtGreen = 0xFF;
            }
        }
    }
    return;
}
