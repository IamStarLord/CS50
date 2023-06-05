#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    // prompt the  user for the height of the pyramid
    do
    {
        n = get_int("Height: ");
    }
    while (n <= 0 || n > 8);

    // draw the actual pyramid
    for (int i = 1; i <= n; i++)
    {
        // for each row
        for (int j = i; j < n; j++)
        {
            // print spaces
            printf(" ");
        }
        for (int j = 1; j <= i; j++)
        {
            // print hashes
            printf("#");
        }
        // print two spaces in between
        printf("  ");

        for (int j = 1; j <= i; j++)
        {
            // print hashes
            printf("#");
        }
        // print end of row
        printf("\n");
    }


}