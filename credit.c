/*  Program checks whether a credit card number is valid using luhn's algorithm.
    It may belong to either AMERICAN EXPRESS, MASTERCARD or VISA.
*/

#include <cs50.h>
#include <stdio.h>
#include <math.h>

int checksum(long num);
int sumDigits1(long num);
int sumDigits2(long num);
int countDigits(long num);
int amex(long num);
int mastercard(long num);
int visa(long num);


int main(void)
{
    // Input credit card number
    long num = get_long("Number: ");
    // Validate checksum
    if (checksum(num) == 1)
    {
        // Check if card belongs to AMERICAN EXPRESS
        if (amex(num) == 1)
        {
            printf("AMEX\n");
        }
        // Check if card belongs to MASTERCARD
        else if (mastercard(num) == 1)
        {
            printf("MASTERCARD\n");
        }
        // Check if card belongs to VISA
        else if (visa(num) == 1)
        {
            printf("VISA\n");
        }
        // Print invalid if card doesn't belong to any bank
        else
        {
            printf("INVALID\n");
        }
    }
    // Print invalid if checksum fails
    else
    {
        printf("INVALID\n");
    }
    return 0;
}

// Check if card number follows LUHN'S ALGORITHM
int checksum(long num)
{
    int valid = 0;
    int sum = sumDigits1(num) + sumDigits2(num);
    if (sum % 10 == 0)
    {
        valid = 1;
    }
    return valid;
}

/*  Multiply every other digit by 2, starting with the number's second-to-last digit
    And then add those products' digits together
*/
int sumDigits1(long num)
{
    // N *= 10 adds a zero at the end thus shifting the digits making it easy to extract the second-to-last digit
    num *= 10;
    int sum = 0;
    while (num > 0)
    {
        int product = (num % 10) * 2;
        // Add each digit of product to sum
        while (product > 0)
        {
            sum += (product % 10);
            product /= 10;
        }
        num /= 100;
    }printf("\nsumDigits1= %d\n", sum);
    return sum;
}

// Sum the digits that weren’t multiplied by 2
int sumDigits2(long num)
{
    int sum = 0;
    while (num > 0)
    {
        sum += (num % 10);
        num /= 100;
    }printf("\nsumDigits2= %d\n", sum);
    return sum;
}

// Count the number of digits
int countDigits(long num)
{
    int count = 0;
    while (num > 0)
    {
        num /= 10;
        ++count;
    }printf("\ncount= %d\n", count);
    return count;
}

// Check if the card belongs to american express
int amex(long num)
{
    int valid = 0;
    // Check if there are 15 digits in card number
    if (countDigits(num) == 15)
    {
        int first2digits = num / pow(10, 13);
        // Check if the first 2 digits of the card number matches
        if (first2digits == 34 || first2digits == 37)
        {
            valid = 1;
        }
    }
    return valid;
}

// Check if the card belongs to mastercard
int mastercard(long num)
{
    int valid = 0;
    // Check if there are 16 digits in card number
    if (countDigits(num) == 16)
    {
        int first2digits = num / pow(10, 14);
        // Check if the first 2 digits of the card number matches
        if (first2digits == 51 || first2digits == 52 || first2digits == 53 || first2digits == 54 || first2digits == 55)
        {
            valid = 1;
        }
    }
    return valid;
}

// Check if the card belongs to visa
int visa(long num)
{
    int valid = 0, digitcount = countDigits(num);
    // Check if there are 13 digits in card number
    if (digitcount == 13)
    {
        int firstdigit = num / pow(10, 12);
        // Check if the first digit is 4
        if (firstdigit == 4)
        {
            valid = 1;
        }
    }
    // Check if there are 16 digits in card number
    if (digitcount == 16)
    {
        int firstdigit = num / pow(10, 15);
        // Check if the first digit is 4
        if (firstdigit == 4)
        {
            valid = 1;
        }
    }
    return valid;
}
