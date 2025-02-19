#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height, column, row, space;
    do
    {
        height = get_int("Choose height between 1 and 8: ");
    }
    while(height < 1 || height > 8);

    for(column= 0; column< height; column++)
    {
        for(space= 0; space< height-column-1; space++)
        {
            printf(" ");
        }
        for(row= 0; row<= column; row++)
        {
            printf("#");
        }
        printf("\n");
    }
}