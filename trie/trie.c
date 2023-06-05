// Saves popular dog names in a trie
// https://www.dailypaws.com/dogs-puppies/dog-names/common-dog-names

#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// constont definitions
#define SIZE_OF_ALPHABET 26
// maximum characters a dog name can be
#define MAXCHAR 20

typedef struct node
{
    bool is_word;
    // pointer to an array called children ?
    struct node *children[SIZE_OF_ALPHABET];
}
node;

// Function prototypes
bool check(char *word);
bool unload(void);
void unloader(node *current);

// Root of trie
node *root;

// Buffer to read dog names into
char name[MAXCHAR];

int main(int argc, char *argv[])
{
    // Check for command line args
    if (argc != 2)
    {
        printf("Usage: ./trie infile\n");
        return 1;
    }

    // File with names
    FILE *infile = fopen(argv[1], "r");
    if (!infile)
    {
        printf("Error opening file!\n");
        return 1;
    }

    // Allocate root of trie
    root = malloc(sizeof(node));

    if (root == NULL)
    {
        return 1;
    }

    root->is_word = false;
    for (int i = 0; i < SIZE_OF_ALPHABET; i++)
    {
        // allocate all the children[i] to NULL (no memory allocated yet)
        root->children[i] = NULL;
    }

    // gets a word of a maximal length
    // Add words to the trie
    // make sure a valid value is returned
    while (fscanf(infile, "%s", name) == 1)
    {
        // cursor to traverse
        node *cursor = root;

        // iterate through the characters in the name
        for (int i = 0, n = strlen(name); i < n; i++)
        {
            // lower the alphabet and substract 'a' from the ascii alphabet
            // to get 0 indexed values
            int index = tolower(name[i]) - 'a';
            // if there is no node at the children
            if (cursor->children[index] == NULL)
            {

                // Make node
                node *new = malloc(sizeof(node));
                // not a word so far
                new->is_word = false;
                for (int j = 0; j < SIZE_OF_ALPHABET; j++)
                {
                    // for each of the alphabets make the node's children NULL
                    new->children[j] = NULL;
                }
                // point the child node at cursor to the node
                cursor->children[index] = new;
            }

            // Go to node which we may have just been made
            // go to the next node
            cursor = cursor->children[index];
        }

        // if we are at the end of the word, mark it as being a word
        cursor->is_word = true;
    }

    if (check(get_string("Check word: ")))
    {
        printf("Found!\n");
    }
    else
    {
        printf("Not Found.\n");
    }

    if (!unload())
    {
        printf("Problem freeing memory!\n");
        return 1;
    }

    fclose(infile);
}

// TODO: Complete the check function, return true if found, false if not found
bool check(char* word)
{
    // cursor to iterate through the trie
    node *cursor = root;
    // char to hold character
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        // get index of the char
        int index = tolower(word[i]) - 'a';
        // if we have reached the last character, check if current node is a word
        if (word[i + 1] == '\0' && cursor->children[index]->is_word)
        {
            return true;
        }
        // otherwise check if the character is not NULL
        // and move to the next cursor
        else if (cursor->children[index] != NULL)
        {
          // move cursor to point to the next node
          cursor = cursor->children[index];
        }
    }
    // if we have reached this far, we didn't find the word
    return false;
}

// Unload trie from memory
bool unload(void)
{

    // The recursive function handles all of the freeing
    unloader(root);

    return true;
}

void unloader(node* current)
{

    // Iterate over all the children to see if they point to anything and go
    // there if they do point
    for (int i = 0; i < SIZE_OF_ALPHABET; i++)
    {
        if (current->children[i] != NULL)
        {
            unloader(current->children[i]);
        }
    }

    // After we check all the children point to null we can get rid of the node
    // and return to the previous iteration of this function.
    free(current);
}
