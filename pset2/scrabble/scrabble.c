#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!");
    }
    else
    {
        printf("Tie!");
    }
    printf("\n");
}

int compute_score(string word)
{
    int score = 0;

    for (int i = 0; i < strlen(word); i++)
    {
        if (islower(word[i]))   //check lowercase
        {
            int character1 = word[i] - 'a';
            score += POINTS[character1]; //h ascii=104 104-97=7 posº7
        }
        else if (isupper(word[i]))  //check uppercase
        {
            int character2 = word[i] - 'A';
            score += POINTS[character2];
        }
    }
    return score;
}