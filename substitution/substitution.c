#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

bool isduplicate(string key);
bool isalphastring(string s);

int main(int argc, string argv[])
{
    // if less than 2 arguments or more than 2 arguments
    if (argc < 2 || argc > 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // save the key in a variable
    string key = (string) argv[1];
    // save key length in a variable
    int keylen = strlen(key);
    // if the key is invalid
    // i.e. does not contain 26 letters
    // does not contain non-alphabetical characters
    // contains each letter exactly once
    // printf an error message and return 1
    if (keylen != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else if (!(isalphastring(key)))
    {
        printf("Key must be alphabetical.\n");
        return 1;
    }
    else if (isduplicate(key))
    {
        printf("Key must not contain duplicate letters.\n");
        return 1;
    }

    // prompt the user for plaintext
    string plaintext = get_string("Plaintext:  ");
    printf("ciphertext: ");
    // variable to index into the key
    int k = 0;
    // for each letter in the plaintext
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        // if the plaintext is A
        // then index is 0
        if (isalpha(plaintext[i]))
        {
            if (isupper(plaintext[i]))
            {
                // get index corresponding to the key array
                k = plaintext[i] - (int) 'A';
                // replace plaintext
                // by indexing into the key at k
                plaintext[i] = toupper(key[k]);
            }
            else
            {
                // get index corresponding to the key array
                k = plaintext[i] - (int) 'a';
                // replace plaintext
                // by indexing into the key at k
                plaintext[i] = tolower(key[k]);
            }
        }

        printf("%c", plaintext[i]);
    }
    printf("\n");
}

bool isduplicate(string key)
{
    int n = strlen(key);
    // for each character in key
    for (int i = 0; i < n; i++)
    {
        // for every other character in key
        for (int j = 0; j < n; j++)
        {
            // skip the same character on the same position
            if (i == j)
            {
                continue;
            }
            // check if a character is repeated twice
            else if (key[i] == key[j])
            {
                printf("duplicate letter %c\n", key[i]);
                return true;
            }

        }
    }
    // else return false
    return false;
}

bool isalphastring(string s)
{
    // for each character in the string
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        // if character is not alphabetic
        if (!isalpha(s[i]))
        {
            return false;
        }
    }
    return true;
}
