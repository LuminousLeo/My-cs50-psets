#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int i;  //height of piramid
    int a;  //column piramid1
    int b;  //row piramid 1
    int c;  //right alignment piramid1
    int d;  //column piramid2
    int e;  //row piramid2

    do
    {
        i = get_int("Height: ");    //promt user to choose height
    }
    while (i < 1 || i > 8);

    for (a = 0; a < i; a++)
    {
        for (c = i - 1; c > a; c--)
        {
            printf(" ");
        }
        printf("#");

        for (b = 0; b < a; b++)
        {
            printf("#");
        }

        for (d = a; d == a; d++)
        {
            printf("  #");

            for (e = 0; e < b; e++)
            {
                printf("#");
            }
        }
        printf("\n");
    }
}