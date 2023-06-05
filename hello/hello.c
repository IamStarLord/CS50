#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Take input from the user
    // string name = get_string("What's your name?\n");
    // // Print user input
    // printf("hello, %s\n", name);
    int width = 6;
    int row[6];
    row[0] = 0;
    row[1] = 1;
    row[2] = 2;
    row[3] = 3;
    row[4] = 4;
    row[5] = 5;

    printf("Array before reversing: ");

    for (int i = 0; i < 6; i++)
    {
        printf("%i, ", row[i]);
    }

    printf("\n");
    for (int j = 0; j < (width / 2); j++)
    {
        // reverse the row
        int pixel1 = row[j];
        int pixel2 = row[(width - 1) - j];

        int temp = pixel1;
        pixel1 = pixel2;
        pixel2 = temp;

        row[j] = pixel1;
        row[(width - 1) - j] = pixel2;
        // 14 - 0 = 14
        // 14 - 1 = 13
        // 14 - 2 = 12
        // 14 - 3 = 11
        // 14 - 4 = 10
        // 14 - 5 = 9
        // 14 - 6 = 8
        // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14

    }

    printf("Array after reversing: ");

    for (int i = 0; i < 6; i++)
    {
        printf("%i, ", row[i]);
    }

    printf("\n");

}