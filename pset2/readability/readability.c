#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");
    float number_of_letters = count_letters(text);
    float number_of_words = count_words(text);
    float number_of_sentences = count_sentences(text);
    float letters_per_100 = (number_of_letters / number_of_words) * 100;  //l
    float sentences_per_100 = (number_of_sentences / number_of_words) * 100;  //s
    float grade_level = (0.0588 * letters_per_100) - (0.296 * sentences_per_100) - 15.8; //calculate grade
    int j = round(grade_level); //getting rid of the zeros

    if (j >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (j < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", j);
    }

}



int count_letters(string text)  //counts the number of letters
{
    int letters = strlen(text);
    for (int i = 0; i < strlen(text); i++)
    {
        if (isspace(text[i]) || ispunct(text[i]) || isdigit(text[i]))
        {
            letters--;
        }
    }
    return letters;
}

int count_words(string text)    //counts the number of words
{
    int word = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isspace(text[i]))
        {
            word++;
        }
    }
    word++;
    return word;
}

int count_sentences(string text)    //counts the number od sentences
{
    int sentences = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }
    return sentences;
}