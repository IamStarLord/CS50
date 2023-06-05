// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // open dictionary file (use fopen and check for NULL)
    FILE *infile = fopen(dictionary, "r");
    if (infile == NULL)
    {
        printf("Error opening dictionary file!\n");
        return false;
    }
    // read strings from file one at a time
    node *new = malloc(sizeof(node));
    char new_word[LENGTH + 1];

    while (fscanf(infile, "%s", new_word) == 1)
    {
        if (new == NULL)
        {
            printf("Not enough memory");
            return false;
        }
        // create a new node for each word
        strcpy(new->word, new_word);
        // make node's next point to NULL
        new->next = NULL;
        // index word
        int index = hash(new_word);
        // insert this node at the front of the linked list

        // case 1: either there is nothing at this place
        if (table[index] == NULL)
        {
            // point to wherever the new node is pointing
            table[index] = new;
        }
        // case 2: there is already something inserted there
        else
        {
            // make new node's next point to wherever the head is pointing
            new->next = table[index];
            // make head point to the new node
            table[index] = new;

        }
    }
    // if we got here, dictionary has been loaded
    // free allocated memory
    free(new);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    return false;
}
