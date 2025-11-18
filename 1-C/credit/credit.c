#include <stdio.h>
#include <stdbool.h> 
#include <string.h>
#include <stdlib.h>

long long get_num(void);
bool valid(long long number);
void check_ccn(long long ccn, bool valid);

int num_length = 0;

int main(void)
{
    // Prompt the usrer for a credit card number
    long long card_number = get_num();

    // Check the validation of the number
    bool validation = valid(card_number);

    // Check for card number length and starting digits and Print the results
    check_ccn(card_number, validation);
}

long long get_num(void)
{
    long long cc_num = 0;
    do
    {
    printf("Number: ");
    scanf("%lld", &cc_num);
    }
    while (cc_num < 0);
    return cc_num;
}

bool valid(long long number)
{  
    char str_num[30];
    // Convert the long long to a string
    // snprintf is safer than sprintf as it prevents buffer overflows
    snprintf(str_num, sizeof(str_num), "%lld", number);
    
    num_length = strlen(str_num);
    int sum = 0;

    // Calculate the sum of products’ digits
    if (num_length % 2 == 0)
    {
        for (int i = 0; i < num_length; i++)
        {
            if (i % 2 == 0)
            {
                // Convert the character digit to its integer value
                int digit = str_num[i] - '0';
                // Mutliply by 2
                int mtb = digit * 2;

                int product_digit;
                if (mtb > 9)
                {
                    // To get the first digit of a number made of two didgits I divid by 10
                    int d1 = mtb/10;
                    int d2 = mtb % 10;
                    product_digit = d1 + d2;
                }
                else
                {
                    product_digit = mtb;
                }
                sum += product_digit;
            }
        }
    }
    else
    {
        for (int i = 0; i < num_length; i++)
        {
            if (i % 2 != 0)
            {
                // Convert the character digit to its integer value
                int digit = str_num[i] - '0';
                // Mutliply by 2
                int mtb = digit * 2;

                int product_digit;
                if (mtb > 9)
                {
                    int d1 = mtb/10;
                    int d2 = mtb % 10;
                    product_digit = d1 + d2;
                }
                else
                {
                    product_digit = mtb;
                }
                sum += product_digit;
            }
        }             
    }

    // Calculate the sum of the digits that weren’t multiplied by 2
    if (num_length % 2 != 0)
    {
        for (int i = 0; i < num_length; i++)
        {
            if (i % 2 == 0)
            {
                // Convert the character digit to its integer value
                int digit = str_num[i] - '0';
                sum += digit;
            }
        }
    }
    else
    {
        for (int i = 0; i < num_length; i++)
        {
            if (i % 2 != 0)
            {
                int digit = str_num[i] - '0';
                sum += digit;
            }
        }             
    }
    // Check the last digit of sum
    if (sum % 10 == 0)
    { 
        return true;
    }
    else
    {
        return false;
    }
}

void check_ccn(long long ccn, bool valid)
{
    // Get the first two digits of the ccn
    long long first2digits = ccn;
    do
    {
        if (first2digits < 100)
        {
            break;
        }
        else
        {
            first2digits /= 10;
        }
    }
    while (first2digits >= 100);
    // Check which CCN, and if valid
    if (valid)
    {
        if (num_length == 15 && (first2digits == 34 || first2digits == 37))
        {
            printf("AMEX\n");
        }
        else if (num_length == 16 && 50 < first2digits && first2digits < 56)
        {
            printf("MASTERCARD\n");
        }
        else if ((num_length == 13 || num_length == 16) && (39 < first2digits && first2digits < 50))
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
