#include <cs50.h>
#include <stdio.h>

int get_years(int start);

int main(void)
{
    int i;  //Start population
    int j;  //End population
    int n = 0;  //nº of years

    // TODO: Prompt for start size
    do
    {
        i = get_int("Start size: \n");
    }
    while (i < 9);

    // TODO: Prompt for end size
    do
    {
        j = get_int("End size: \n");
    }
    while (j < i);

    // TODO: Calculate number of years until we reach threshold
    if (i == j) //Start = end
    {
        n = 0;
    }
    else
    {
        do  //End bigger than start
        {
            i = get_years(i);
            n++;
        }
        while (i < j);
    }


    // TODO: Print number of years
    printf("Years: %i\n", n);
}

int get_years(int start)
{
    return start + ((start / 3) - (start / 4));
}