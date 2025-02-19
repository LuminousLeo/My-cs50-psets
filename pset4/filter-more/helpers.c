#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int averager;
    float red;
    float green;
    float blue;

    for (int i = 0; i <= height - 1; i++)
    {
        for (int j = 0; j <= width - 1; j++)
        {
            red = image[i][j].rgbtRed;
            green = image[i][j].rgbtGreen;
            blue = image[i][j].rgbtBlue;

            //the grayscale calculator<<<<<<<<<<<<<<<<<<<<
            
            averager = round((red + green + blue) / 3);

            image[i][j].rgbtRed = averager;
            image[i][j].rgbtGreen = averager;
            image[i][j].rgbtBlue = averager;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            //switch the pixels
            tmp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE cpy[height][width];
    for (int column = 0; column < height; column++)
    {
        for (int row = 0; row < width; row++)
        {
            cpy[column][row] = image[column][row];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float redx = 0;
            float greenx = 0;
            float bluex = 0;
            float redy = 0;
            float greeny = 0;
            float bluey = 0;
            int red_value = 0;
            int green_value = 0;
            int blue_value = 0;

            //check middle pixels
            if (i < height - 1 && i > 0 && j < width - 1 && j > 0)
            {
                redx = (-cpy[i + 1][j - 1].rgbtRed) + cpy[i + 1][j + 1].rgbtRed + (-2 * cpy[i][j - 1].rgbtRed) + (2 * cpy[i][j + 1].rgbtRed) +
                       (-cpy[i - 1][j - 1].rgbtRed) + cpy[i - 1][j + 1].rgbtRed;
                greenx = (-cpy[i + 1][j - 1].rgbtGreen) + cpy[i + 1][j + 1].rgbtGreen + (-2 * cpy[i][j - 1].rgbtGreen) +
                         (2 * cpy[i][j + 1].rgbtGreen) + (-cpy[i - 1][j - 1].rgbtGreen) + cpy[i - 1][j + 1].rgbtGreen;
                bluex = (-cpy[i + 1][j - 1].rgbtBlue) + cpy[i + 1][j + 1].rgbtBlue + (-2 * cpy[i][j - 1].rgbtBlue) +
                        (2 * cpy[i][j + 1].rgbtBlue) + (-cpy[i - 1][j - 1].rgbtBlue) + cpy[i - 1][j + 1].rgbtBlue;
                redy = (-cpy[i + 1][j - 1].rgbtRed) + (-2 * cpy[i + 1][j].rgbtRed) + (-cpy[i + 1][j + 1].rgbtRed) + cpy[i - 1][j - 1].rgbtRed +
                       (2 * cpy[i - 1][j].rgbtRed) + cpy[i - 1][j + 1].rgbtRed;
                greeny = (-cpy[i + 1][j - 1].rgbtGreen) + (-2 * cpy[i + 1][j].rgbtGreen) + (-cpy[i + 1][j + 1].rgbtGreen) + cpy[i - 1][j -
                         1].rgbtGreen + (2 * cpy[i - 1][j].rgbtGreen) + cpy[i - 1][j + 1].rgbtGreen;
                bluey = (-cpy[i + 1][j - 1].rgbtBlue) + (-2 * cpy[i + 1][j].rgbtBlue) + (-cpy[i + 1][j + 1].rgbtBlue) + cpy[i - 1][j - 1].rgbtBlue
                        + (2 * cpy[i - 1][j].rgbtBlue) + cpy[i - 1][j + 1].rgbtBlue;
            }

            //check right edge
            if (i < height - 1 && i > 0 && j == width - 1)
            {
                redx = (-cpy[i + 1][j - 1].rgbtRed) + (-2 * cpy[i][j - 1].rgbtRed) + (-cpy[i - 1][j - 1].rgbtRed);
                greenx = (-cpy[i + 1][j - 1].rgbtGreen) + (-2 * cpy[i][j - 1].rgbtGreen) + (-cpy[i - 1][j - 1].rgbtGreen);
                bluex = (-cpy[i + 1][j - 1].rgbtBlue) + (-2 * cpy[i][j - 1].rgbtBlue) + (-cpy[i - 1][j - 1].rgbtBlue);
                redy = (-2 * cpy[i + 1][j].rgbtRed) + (-cpy[i + 1][j - 1].rgbtRed) + (2 * cpy[i - 1][j].rgbtRed) + cpy[i - 1][j - 1].rgbtRed;
                greeny = (-2 * cpy[i + 1][j].rgbtGreen) + (-cpy[i + 1][j - 1].rgbtGreen) + (2 * cpy[i - 1][j].rgbtGreen) + cpy[i - 1][j -
                         1].rgbtGreen;
                bluey = (-2 * cpy[i + 1][j].rgbtBlue) + (-cpy[i + 1][j - 1].rgbtBlue) + (2 * cpy[i - 1][j].rgbtBlue) + cpy[i - 1][j - 1].rgbtBlue;
            }

            //check left edge
            if (i < height - 1 && i > 0 && j == 0)
            {
                redx = cpy[i + 1][j + 1].rgbtRed + (2 * cpy[i][j + 1].rgbtRed) + cpy[i - 1][j + 1].rgbtRed;
                greenx = cpy[i + 1][j + 1].rgbtGreen + (2 * cpy[i][j + 1].rgbtGreen) + cpy[i - 1][j + 1].rgbtGreen;
                bluex = cpy[i + 1][j + 1].rgbtBlue + (2 * cpy[i][j + 1].rgbtBlue) + cpy[i - 1][j + 1].rgbtBlue;
                redy = (-2 * cpy[i + 1][j].rgbtRed) + (-cpy[i + 1][j + 1].rgbtRed) + (2 * cpy[i - 1][j].rgbtRed) + cpy[i - 1][j + 1].rgbtRed;
                greeny = (-2 * cpy[i + 1][j].rgbtGreen) + (-cpy[i + 1][j + 1].rgbtGreen) + (2 * cpy[i - 1][j].rgbtGreen) + cpy[i - 1][j +
                         1].rgbtGreen;
                bluey = (-2 * cpy[i + 1][j].rgbtBlue) + (-cpy[i + 1][j + 1].rgbtBlue) + (2 * cpy[i - 1][j].rgbtBlue) + cpy[i - 1][j + 1].rgbtBlue;
            }

            //check upper edge
            if (i == height - 1 && j > 0 && j < width - 1)
            {
                redx = (-2 * cpy[i][j - 1].rgbtRed) + (2 * cpy[i][j + 1].rgbtRed) + (-cpy[i - 1][j - 1].rgbtRed) + cpy[i - 1][j + 1].rgbtRed;
                greenx = (-2 * cpy[i][j - 1].rgbtGreen) + (2 * cpy[i][j + 1].rgbtGreen) + (-cpy[i - 1][j - 1].rgbtGreen) + cpy[i - 1][j +
                         1].rgbtGreen;
                bluex = (-2 * cpy[i][j - 1].rgbtBlue) + (2 * cpy[i][j + 1].rgbtBlue) + (-cpy[i - 1][j - 1].rgbtBlue) + cpy[i - 1][j + 1].rgbtBlue;
                redy = cpy[i - 1][j - 1].rgbtRed + (2 * cpy[i - 1][j].rgbtRed) + cpy[i - 1][j + 1].rgbtRed;
                greeny = cpy[i - 1][j - 1].rgbtGreen + (2 * cpy[i - 1][j].rgbtGreen) + cpy[i - 1][j + 1].rgbtGreen;
                bluey = cpy[i - 1][j - 1].rgbtBlue + (2 * cpy[i - 1][j].rgbtBlue) + cpy[i - 1][j + 1].rgbtBlue;
            }

            //check lower edge
            if (i == 0 && j > 0 && j < width - 1)
            {
                redx = (-2 * cpy[i][j - 1].rgbtRed) + (2 * cpy[i][j + 1].rgbtRed) + (-cpy[i + 1][j - 1].rgbtRed) + cpy[i + 1][j + 1].rgbtRed;
                greenx = (-2 * cpy[i][j - 1].rgbtGreen) + (2 * cpy[i][j + 1].rgbtGreen) + (-cpy[i + 1][j - 1].rgbtGreen) + cpy[i + 1][j +
                         1].rgbtGreen;
                bluex = (-2 * cpy[i][j - 1].rgbtBlue) + (2 * cpy[i][j + 1].rgbtBlue) + (-cpy[i + 1][j - 1].rgbtBlue) + cpy[i + 1][j + 1].rgbtBlue;
                redy = (-cpy[i + 1][j - 1].rgbtRed) + (-2 * cpy[i + 1][j].rgbtRed) + (-cpy[i + 1][j + 1].rgbtRed);
                greeny = (-cpy[i + 1][j - 1].rgbtGreen) + (-2 * cpy[i + 1][j].rgbtGreen) + (-cpy[i + 1][j + 1].rgbtGreen);
                bluey = (-cpy[i + 1][j - 1].rgbtBlue) + (-2 * cpy[i + 1][j].rgbtBlue) + (-cpy[i + 1][j + 1].rgbtBlue);
            }

            //check upper right corner
            if (i == height - 1 && j == width - 1)
            {
                redx = (-2 * cpy[i][j - 1].rgbtRed) + (-cpy[i - 1][j - 1].rgbtRed);
                greenx = (-2 * cpy[i][j - 1].rgbtGreen) + (-cpy[i - 1][j - 1].rgbtGreen);
                bluex = (-2 * cpy[i][j - 1].rgbtBlue) + (-cpy[i - 1][j - 1].rgbtBlue);
                redy = cpy[i - 1][j - 1].rgbtRed + (2 * cpy[i - 1][j].rgbtRed);
                greeny = cpy[i - 1][j - 1].rgbtGreen + (2 * cpy[i - 1][j].rgbtGreen);
                bluey = cpy[i - 1][j - 1].rgbtBlue + (2 * cpy[i - 1][j].rgbtBlue);
            }

            //check upper left corner
            if (i == height - 1 && j == 0)
            {
                redx = (2 * cpy[i][j + 1].rgbtRed) + cpy[i - 1][j + 1].rgbtRed;
                greenx = (2 * cpy[i][j + 1].rgbtGreen) + cpy[i - 1][j + 1].rgbtGreen;
                bluex = (2 * cpy[i][j + 1].rgbtBlue) + cpy[i - 1][j + 1].rgbtBlue;
                redy = (2 * cpy[i - 1][j].rgbtRed) + cpy[i - 1][j + 1].rgbtRed;
                greeny = (2 * cpy[i - 1][j].rgbtGreen) + cpy[i - 1][j + 1].rgbtGreen;
                bluey = (2 * cpy[i - 1][j].rgbtBlue) + cpy[i - 1][j + 1].rgbtBlue;
            }

            //check lower right corner
            if (i == 0 && j == width - 1)
            {
                redx = (-cpy[i + 1][j - 1].rgbtRed) + (-2 * cpy[i][j - 1].rgbtRed);
                greenx = (-cpy[i + 1][j - 1].rgbtGreen) + (-2 * cpy[i][j - 1].rgbtGreen);
                bluex = (-cpy[i + 1][j - 1].rgbtBlue) + (-2 * cpy[i][j - 1].rgbtBlue);
                redy = (-cpy[i + 1][j - 1].rgbtRed) + (-2 * cpy[i + 1][j].rgbtRed);
                greeny = (-cpy[i + 1][j - 1].rgbtGreen) + (-2 * cpy[i + 1][j].rgbtGreen);
                bluey = (-cpy[i + 1][j - 1].rgbtBlue) + (-2 * cpy[i + 1][j].rgbtBlue);
            }

            //check lower left corner
            if (i == 0 && j == 0)
            {
                redx = cpy[i + 1][j + 1].rgbtRed + (2 * cpy[i][j + 1].rgbtRed);
                greenx = cpy[i + 1][j + 1].rgbtGreen + (2 * cpy[i][j + 1].rgbtGreen);
                bluex = cpy[i + 1][j + 1].rgbtBlue + (2 * cpy[i][j + 1].rgbtBlue);
                redy = (-2 * cpy[i + 1][j].rgbtRed) + (-cpy[i + 1][j + 1].rgbtRed);
                greeny = (-2 * cpy[i + 1][j].rgbtGreen) + (-cpy[i + 1][j + 1].rgbtGreen);
                bluey = (-2 * cpy[i + 1][j].rgbtBlue) + (-cpy[i + 1][j + 1].rgbtBlue);
            }

            //get the value of the edge
            red_value = round(sqrt((redx * redx)  + (redy * redy)));
            green_value = round(sqrt((greenx * greenx) + (greeny * greeny)));
            blue_value = round(sqrt((bluex * bluex) + (bluey * bluey)));

            //cap the values at 255
            if (red_value > 255)
            {
                red_value = 255;
            }
            if (green_value > 255)
            {
                green_value = 255;
            }
            if (blue_value > 255)
            {
                blue_value = 255;
            }

            image[i][j].rgbtRed = red_value;
            image[i][j].rgbtGreen = green_value;
            image[i][j].rgbtBlue = blue_value;
        }
    }

    return;
}
