#include "helpers.h"
#include <math.h>

// Convert image to grayscale

void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    double red;
    double green;
    double blue;

    for (int i = 0; i < height; i ++)  //columns
    {
        for (int j = 0; j < width; j++)    //rows
        {
            red = image[i][j].rgbtRed;
            green = image[i][j].rgbtGreen;
            blue = image[i][j].rgbtBlue;

            int converter_value = round((red + green + blue) / 3); //calculate value

            image[i][j].rgbtRed = converter_value;
            image[i][j].rgbtGreen = converter_value;
            image[i][j].rgbtBlue = converter_value;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i ++)  //column
    {
        for (int j = 0; j < width; j++)    //row
        {
            //calculate red
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            //calculate green
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            //calculate blue
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    for (int i = 0; i < height; i ++)   //columns
    {
        for (int j = 0; j < width / 2; j++) //rows
        {
            temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //TODO create a copy image so that you don't immediatly change the color of the pixels

    RGBTRIPLE cpy[height][width];

    for (int column = 0; column < height; column++)
    {
        for (int row = 0; row < width; row++)
        {
            cpy[column][row] = image[column][row];
        }
    }

    for (int i = 0; i < height; i ++)  //columns
    {
        for (int j = 0; j < width; j++)    //rows
        {
            int divider = 0;
            float red = 0;
            float green = 0;
            float blue = 0;

            //check upper right corner
            if (i == height - 1 && j == width - 1)
            {
                red = cpy[i - 1][j].rgbtRed + cpy[i][j - 1].rgbtRed + cpy[i - 1][j - 1].rgbtRed;
                green = cpy[i - 1][j].rgbtGreen + cpy[i][j - 1].rgbtGreen + cpy[i - 1][j - 1].rgbtGreen;
                blue = cpy[i - 1][j].rgbtBlue + cpy[i][j - 1].rgbtBlue + cpy[i - 1][j - 1].rgbtBlue;
                divider = 4;
            }

            //check upper left corner
            if (i == height - 1 && j == 0)
            {
                red = cpy[i - 1][j].rgbtRed + cpy[i][j + 1].rgbtRed + cpy[i - 1][j + 1].rgbtRed;
                green = cpy[i - 1][j].rgbtGreen + cpy[i][j + 1].rgbtGreen + cpy[i - 1][j + 1].rgbtGreen;
                blue = cpy[i - 1][j].rgbtBlue + cpy[i][j + 1].rgbtBlue + cpy[i - 1][j + 1].rgbtBlue;
                divider = 4;
            }

            //check lower right corner
            if (i == 0 && j == width - 1)
            {
                red = cpy[i + 1][j].rgbtRed + cpy[i][j - 1].rgbtRed + cpy[i + 1][j - 1].rgbtRed;
                green = cpy[i + 1][j].rgbtGreen + cpy[i][j - 1].rgbtGreen + cpy[i + 1][j - 1].rgbtGreen;
                blue = cpy[i + 1][j].rgbtBlue + cpy[i][j - 1].rgbtBlue + cpy[i + 1][j - 1].rgbtBlue;
                divider = 4;
            }

            //check lower left corner
            if (i == 0 &&  j == 0)
            {
                red = cpy[i + 1][j].rgbtRed + cpy[i][j + 1].rgbtRed + cpy[i + 1][j + 1].rgbtRed;
                green = cpy[i + 1][j].rgbtGreen + cpy[i][j + 1].rgbtGreen + cpy[i + 1][j + 1].rgbtGreen;
                blue = cpy[i + 1][j].rgbtBlue + cpy[i][j + 1].rgbtBlue + cpy[i + 1][j + 1].rgbtBlue;
                divider = 4;
            }

            //check if right edge
            if (i > 0 && i < height - 1 && j == width - 1)
            {
                red = cpy[i + 1][j].rgbtRed + cpy[i - 1][j].rgbtRed + cpy[i][j - 1].rgbtRed + cpy[i + 1][j - 1].rgbtRed + cpy[i - 1][j - 1].rgbtRed;
                green = cpy[i + 1][j].rgbtGreen + cpy[i - 1][j].rgbtGreen + cpy[i][j - 1].rgbtGreen + cpy[i + 1][j - 1].rgbtGreen + cpy[i - 1][j -
                        1].rgbtGreen;
                blue = cpy[i + 1][j].rgbtBlue + cpy[i - 1][j].rgbtBlue + cpy[i][j - 1].rgbtBlue + cpy[i + 1][j - 1].rgbtBlue + cpy[i - 1][j -
                        1].rgbtBlue;
                divider = 6;
            }

            //check if left edge
            if (i > 0 && i < height - 1 && j == 0)
            {
                red = cpy[i + 1][j].rgbtRed + cpy[i - 1][j].rgbtRed + cpy[i][j + 1].rgbtRed + cpy[i + 1][j + 1].rgbtRed + cpy[i - 1][j + 1].rgbtRed;
                green = cpy[i + 1][j].rgbtGreen + cpy[i - 1][j].rgbtGreen + cpy[i][j + 1].rgbtGreen + cpy[i + 1][j + 1].rgbtGreen + cpy[i - 1][j +
                        1].rgbtGreen;
                blue = cpy[i + 1][j].rgbtBlue + cpy[i - 1][j].rgbtBlue + cpy[i][j + 1].rgbtBlue + cpy[i + 1][j + 1].rgbtBlue + cpy[i - 1][j +
                        1].rgbtBlue;
                divider = 6;
            }

            //check if upper edge
            if (i == height - 1 && j > 0 && j < width - 1)
            {
                red = cpy[i][j - 1].rgbtRed + cpy[i][j + 1].rgbtRed + cpy[i - 1][j].rgbtRed + cpy[i - 1][j - 1].rgbtRed + cpy[i - 1][j + 1].rgbtRed;
                green = cpy[i][j - 1].rgbtGreen + cpy[i][j + 1].rgbtGreen + cpy[i - 1][j].rgbtGreen + cpy[i - 1][j - 1].rgbtGreen + cpy[i - 1][j +
                        1].rgbtGreen;
                blue = cpy[i][j - 1].rgbtBlue + cpy[i][j + 1].rgbtBlue + cpy[i - 1][j].rgbtBlue + cpy[i - 1][j - 1].rgbtBlue + cpy[i - 1][j +
                        1].rgbtBlue;
                divider = 6;
            }

            //check if lower edge
            if (i == 0 && j > 0 && j < width - 1)
            {
                red = cpy[i][j - 1].rgbtRed + cpy[i][j + 1].rgbtRed + cpy[i + 1][j].rgbtRed + cpy[i + 1][j - 1].rgbtRed + cpy[i + 1][j + 1].rgbtRed;
                green = cpy[i][j - 1].rgbtGreen + cpy[i][j + 1].rgbtGreen + cpy[i + 1][j].rgbtGreen + cpy[i + 1][j - 1].rgbtGreen + cpy[i + 1][j +
                        1].rgbtGreen;
                blue = cpy[i][j - 1].rgbtBlue + cpy[i][j + 1].rgbtBlue + cpy[i + 1][j].rgbtBlue + cpy[i + 1][j - 1].rgbtBlue + cpy[i + 1][j +
                        1].rgbtBlue;
                divider = 6;
            }

            //check if pixel in the middle
            if (i < height - 1 && i > 0 && j < width - 1 && j > 0)
            {
                red = cpy[i + 1][j].rgbtRed + cpy[i - 1][j].rgbtRed + cpy[i][j + 1].rgbtRed + cpy[i][j - 1].rgbtRed + cpy[i + 1][j + 1].rgbtRed +
                      cpy[i + 1][j - 1].rgbtRed + cpy[i - 1][j + 1].rgbtRed + cpy[i - 1][j - 1].rgbtRed;
                green = cpy[i + 1][j].rgbtGreen + cpy[i - 1][j].rgbtGreen + cpy[i][j + 1].rgbtGreen + cpy[i][j - 1].rgbtGreen + cpy[i + 1][j +
                        1].rgbtGreen + cpy[i + 1][j - 1].rgbtGreen + cpy[i - 1][j + 1].rgbtGreen + cpy[i - 1][j - 1].rgbtGreen;
                blue = cpy[i + 1][j].rgbtBlue + cpy[i - 1][j].rgbtBlue + cpy[i][j + 1].rgbtBlue + cpy[i][j - 1].rgbtBlue + cpy[i + 1][j +
                        1].rgbtBlue + cpy[i + 1][j - 1].rgbtBlue + cpy[i - 1][j + 1].rgbtBlue + cpy[i - 1][j - 1].rgbtBlue;
                divider = 9;
            }

            image[i][j].rgbtRed = round((image[i][j].rgbtRed + red) / divider);
            image[i][j].rgbtGreen = round((image[i][j].rgbtGreen + green) / divider);
            image[i][j].rgbtBlue = round((image[i][j].rgbtBlue + blue) / divider);
        }
    }
    return;
}
