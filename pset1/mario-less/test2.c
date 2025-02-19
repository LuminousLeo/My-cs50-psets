#include<stdio.h>
#include<cs50.h>

int main(void)
{
    string name = get_string("What's your name?\n");
    for (int x = 0 ; x < 20 ; x++)
    {
        printf("Hello, %s\n", name);
    }
}