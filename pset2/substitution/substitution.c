#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int check_key(string key);  //checks if key is all letters
int duplicate(string key);  //checks if key has duplicates

int main(int argc, string argv[])
{
    string key = argv[1];   //the key
    char c;
    int position;
    if (argc != 2)   //checks if key has more than 1 argument
    {
        printf("error 104: must have a single argument\n");
        return 1;
    }
    else if (strlen(key) != 26 || check_key(key) < 26 || duplicate(key) != 0) 
    {
        printf("error 105: must have all letters of the alphabet\n");
        return 1;
    }
    else
    {
        string plaintext = get_string("plaintext: ");   //gets a message from user
        printf("ciphertext: ");
        for (int i = 0; i < strlen(plaintext); i++) //encryption process
        {
            c = plaintext[i];
            position = plaintext[i];    // a = posº 97
            if (islower(c))
            {
                position -= 96; //97 - 96
                c = key[position - 1];  //1 - 1 = 0, gets the position of the letters thats going to substitute
                c = tolower(c);
            }
            else if (isupper(c))
            {
                position -= 64;
                c = key[position - 1];
                c = toupper(c);
            }
            printf("%c", c);
        }
        printf("\n");
    }
}   //end of main


int check_key(string key)
{
    int checker = 0;
    for (int i = 0; i < strlen(key); i++)
    {
        if (isalpha(key[i]))
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


int duplicate(string key)
{
    char c;
    char d;
    int duplicate = 0;
    for (int i = 0; i < strlen(key); i++)
    {

        c = key[i];
        for (int j = 1 + i; j < strlen(key); j++)
        {
            d = key[j];
            if (c == d)
            {
                duplicate++;
            }
        }
    }
    return duplicate;
}
