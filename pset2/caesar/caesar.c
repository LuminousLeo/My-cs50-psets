#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_key(string key);  //checks if argv is all digits
int lower_encrypt(int lower, int key);   //encrypts lowercase
int upper_encrypt(int upper, int key);   //encrypts uppercase

int main(int argc, string argv[])
{
    string key = argv[1];   //the key
    char c;
    if (argc != 2)   //checks if it has more than 1 argument
    {
        printf("error 104: needs to have one argument\n");
        return 1;
    }

    int checker = check_key(key);
    if (checker > 0) //checks if the string is all numebrs
    {
        int encrypt = atoi(key); //turn string into number
        string plaintext = get_string("plaintext:  ");    //getting the message from the user
        printf("ciphertext: ");
        for (int j = 0; j < strlen(plaintext); j++)
        {
            c = plaintext[j];
            if (islower(c))    //check if letter is lowercase
            {
                c = lower_encrypt(c, encrypt);
            }
            else if (isupper(c))   //check if letter is uppercase
            {
                c = upper_encrypt(c, encrypt);
            }
            printf("%c", c);
        }
        printf("\n");
        return 0;
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}   //end of main



int check_key(string key)
{
    int checker = 0;
    for (int i = 0; i < strlen(key); i++)
    {
        if (isdigit(key[i]))
        {
            checker++;
        }
        else
        {
            checker --;
        }
    }
    return checker;
}   //end of check_key


int lower_encrypt(int lower, int key)
{
    lower = ((lower - 'a') + key) % 26 + 'a';
    return lower;
}


int upper_encrypt(int upper, int key)
{
    upper = ((upper - 'A') + key) % 26 + 'A';
    return upper;
}