#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    string message = get_string("Message: ");   //prompt user for a message
    for (int i = 0; i < strlen(message); i++)   //convert message to binary
    {
        int bit_length[8];
        int j = message[i];
        int size_of_array = 0;

        do
        {
            bit_length[size_of_array] = j % 2;
            j /= 2;
            size_of_array++;
        }
        while (j > 0);

        if (ispunct(message[i]) || isspace(message[i]) || isdigit(message[i]))  //check for punct
        {
            size_of_array++;
        }

        for (int l = size_of_array; l > -1; l--)    //print the message the correct way
        {
            int k = bit_length[l];
            print_bulb(k);
        }

        for (int x = 0; x < 8; x++) //reset array
        {
            bit_length[x] = 0;
        }
        printf("\n");
    }
}



void print_bulb(int bit)
{
    if (bit == 0)   //this is the bulb emoji
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}