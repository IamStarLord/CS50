#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    long card = get_long("Number: ");
    // long card = 4003600000000014;
    long copy = card;
    int checksum = 0;
    int len = 0;
    while (true)
    {
        // get the odd numbered digit from the card number
        int od_num = copy % 10;
        // add the odd numbered digit to the checksum
        checksum += od_num;
        // add 1 to the length
        len += 1;
        // remove the odd numbered digit from the card number
        copy /= 10;
        if (copy == 0)
        {
            break;
        }
        // get the even numbered digit from the card number
        int ev_num = copy % 10;
        // multiply the even numbered digit by 2
        ev_num *= 2;
        // check if the product is double digit number
        if ((ev_num / 10) != 0)
        {
            // printf("The double digit number is %i \n", num);
            int temp = ev_num % 10;
            ev_num /= 10;
            checksum += temp;
        }
        // add the even numbered digit in the checksum
        checksum += ev_num;
        // add 1 to the length
        len += 1;
        // remove the even numbered digit from the card number
        copy /= 10;
        if (copy == 0)
        {
            break;
        }
    }
    // printf("%i\n", len);

    // if the checksum is not divisible by 10, then it is invalid
    printf("%i \n", checksum);
    if (checksum % 10)
    {
        printf("INVALID\n");
    }
    else
    {
        // if the checksum is divisible by 10 then,
        // check the length of the card number
        if (len == 16)
        {
            int digits = card / 100000000000000;
            // printf("%i \n", digits);
            if ((digits == 51) || (digits == 52) || (digits == 53) || (digits == 54) || (digits == 55))
            {
                printf("MASTERCARD\n");
            }
            else if ((digits / 10) == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (len == 15)
        {
            int digits = card / 10000000000000;
            if ((digits == 34) || (digits == 37))
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (len == 13)
        {
            int digits = card / 1000000000000;
            if (digits == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }

}