// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <cs50.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 676;

// Hash table
node *table[N];

// Number of words
unsigned int number_of_words = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int h = hash(word);
    node *cursor = table[h];

    // compares if the word is in the linked list of the position based on the first letter
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
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
    int hash = 0;
    int word_length = strlen(word);
    int prime_number = 41;

    for (int i = 0; i < word_length; i++)
    {
        hash = hash + (prime_number * tolower(word[i]));
    }

    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");

    if (file == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];

    // generates node for each word in the file
    while (fscanf(file, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            return false;
        }

        int h = hash(word);
        strcpy(n->word, word);
        n->next = NULL;

        // if the linked list in the position of the generated hash is empty it is added in the first position
        if (table[h] == NULL)
        {
            table[h] = n;
        }
        // else is added as the last node
        else
        {
            n->next = table[h];
            table[h] = n;
        }

        number_of_words++;
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if no t yet loaded
unsigned int size(void)
{
    return number_of_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }
    }

    return true;
}
