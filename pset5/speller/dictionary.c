// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26 * LENGTH;
int number_of_words;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    //obtain hash value for the word
    int index = hash(word);

    //create cursor and move it to the head of the linked ls
    node *cursor = table[index];

    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int index = 0;

    for (int i = 0; i < strlen(word); i++)
    {
        index += tolower(word[i]);
    }

    return index % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    //open dictionary
    FILE *inptr = fopen(dictionary, "r");
    if (inptr == NULL)
    {
        fclose(inptr);
        return false;
    }

    char load_buffer[LENGTH];
    //read evry word 1 by 1
    while (fscanf(inptr, "%s", load_buffer) != EOF)
    {
        //allocate memory for new word
        node *new = malloc(sizeof(node));
        int index;
        if (new == NULL)
        {
            fclose(inptr);
            return false;
        }

        //copy word from buffer and put it into hash table
        strcpy(new->word, load_buffer);
        index = hash(new->word);
        new->next = table[index];
        table[index] = new;
        number_of_words++;
    }

    fclose(inptr);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return number_of_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *cursor = NULL;
    node *tmp = NULL;

    for (int i = 0; i < N; i++)
    {
        cursor = table[i];
        tmp = table[i];

        while (cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }

    return true;
}