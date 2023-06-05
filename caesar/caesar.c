#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

bool only_digits(string s);
char rotate(char c, int n);

int main(int argc, string argv[])
{
    if (argc < 2)
    {
        // if no key is given
        printf("Usage: ./ceaser key\n");
        return 1;
    }
    else if (argc > 2)
    {
        // if more than one key is given
        printf("Usage: ./ceaser key\n");
        return 1;
    }
    else if (!only_digits(argv[1]))
    {
        // if given key is not an integer
        printf("Usage: ./ceaser key\n");
        return 1;
    }

    // if argument count is 2 and the key is an integer

    // algorithm
    // take the integer key
    int key = atoi(argv[1]);
    // take string input from the user
    string plaintext = get_string("plaintext:  ");
    // iterate through each character in the string
    printf("ciphertext: ");
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        // rotate and print each character
        printf("%c", rotate(plaintext[i], key));
    }
    printf("\n");
}

bool only_digits(string s)
{
    // iterate through each character in the string
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}

// function rotate that takes in a char and int and returns a char rotated some integer places
char rotate(char c, int n)
{
    // if char is alphabetic
    if (isalpha(c))
    {
        // then check if it is lower
        if (islower(c))
        {
            // subtract lowercase a to make a index 0
            c = (c - (int) 'a' + n) % 26;
            // add back a and return
            return c + (int) 'a';
        }
        // if it is upper
        else
        {
            // subtract uppercase A to make A index 0
            c = (c - (int) 'A' + n) % 26;
            // add back a and return
            return c + (int) 'A';
        }
    }
    // if not alphabetic return as it is
    return c;
}