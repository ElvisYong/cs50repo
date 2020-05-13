#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>

int concat(long long a, long long b)
{
    char s1[20];
    char s2[20];

    // Convert both the integers to string
    sprintf(s1, "%lld", a);
    sprintf(s2, "%lld", b);

    // Concatenate both strings
    strcat(s1, s2);

    // Convert the concatenated string
    // to integer
    int c = atoi(s1);

    // return the formed integer
    return c;
}

bool checkAmex(long long a, long long b)
{
    int digit = concat(a,b);

    switch(digit)
    {
        case 34:
            return true;
        case 37:
            return true;
        default:
            return false;
    }
}

bool checkMaster(long long a, long long b)
{
    int digit = concat(a,b);

    switch(digit)
    {
        case 51:
            return true;
        case 52:
            return true;
        case 53:
            return true;
        case 54:
            return true;
        case 55:
            return true;
        default:
            return false;
    }
}

int main(void)
{
    long long input = get_long("Type your credit card number: \n");
    printf("Number: %lld\n", input);

    int counter = 0;
    long long inputArr[16];

    while(input > 0)
    {
        long long digit = input % 10;
        inputArr[counter] = digit;
        counter++;

        // divide 10 to get the next digit
        input /= 10;
    }

    long long totalSum = 0;
    for(int i = 1; i < 16; i += 2)
    {
        long long altsum = inputArr[i] * 2;
        while(altsum > 0)
        {
            totalSum += altsum % 10;
            altsum /= 10;
        }
    }

    for(int i = 0; i < 16; i += 2)
    {
        totalSum += inputArr[i];
    }

    // Catch invalid input
    if(((counter < 13 || counter > 16) && counter != 14 )|| (totalSum % 10) != 0)
    {
        printf("INVALID\n");
    }
    // Catch Amex input
    else if(counter == 15 && checkAmex(inputArr[14], inputArr[13]) && (totalSum % 10) == 0)
    {
        printf("AMEX\n");
    }
     // Catch Mastercard input
    else if(counter == 16 && checkMaster(inputArr[15], inputArr[14]) && (totalSum % 10) == 0)
    {
        printf("MASTERCARD\n");
    }
     // Catch Visa input
    else if((counter == 13 || counter == 16) && (totalSum % 10) == 0)
    {
        if(counter == 13 && inputArr[12] == 4){
            printf("VISA\n");
        }

        if(counter == 16 && inputArr[15] == 4){
            printf("VISA\n");
        }
        else{
             printf("INVALID\n");
        }

    }
    else{
        printf("INVALID\n");
    }
}