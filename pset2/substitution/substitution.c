#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>

int MAX_SIZE = 26;

int main(int argc, string argv[])
{
    string key = argv[1];
    if(argc != 2)
    {
        printf("Usage: ./substituition key\n");
        return 1;
    }

    if(strlen(argv[1]) != MAX_SIZE)
    {
        printf("Key must contain 26 charcter\n");
        return 1;
    }

    regex_t regex;
    char *Expression = "[^A-Za-z]";

    int reti = regcomp(&regex, Expression, REG_EXTENDED | REG_ICASE);
    if(reti != 0)
    {
        printf("regcomp has failed\n");
        return 1;
    }

    reti = regexec(&regex, key, 0, NULL, 0);
    if (!reti)
    {
        printf("Key must not contain anything other than alphabetical characters.\n");
        return 1;
    }

    bool duplicateCharArr[MAX_SIZE];

    for(int i = 0; i < MAX_SIZE; i++)
    {
        duplicateCharArr[i] = false;

    }

    for(int i = 0; i < MAX_SIZE; i++)
    {
        int upperCasedKeyChar = (int)toupper(key[i]);
        int index = upperCasedKeyChar - 65;
        if(duplicateCharArr[index] == false)
        {
            // Mark this alphabet as checked.
            duplicateCharArr[index] = true;
        }
        else
        {
            printf("Key cannot have duplicate characters\n");
            return 1;
        }
    }

    // -22 from small case = uppercase
    string plaintext = get_string("plaintext: ");
    char cipheredText[strlen(plaintext) + 1];
    cipheredText[strlen(plaintext)] = '\0';

    int indexToCipher;

    for(int i = 0; i < strlen(plaintext); i++)
    {
        if(plaintext[i] >= 97 && plaintext[i] <= 122)
        {
            indexToCipher = plaintext[i] - 97;
            cipheredText[i] = tolower(key[indexToCipher]);
        }
        else if(plaintext[i] >= 65 && plaintext[i] <= 90)
        {
            indexToCipher = plaintext[i] - 65;
            cipheredText[i] = toupper(key[indexToCipher]);
        }
        else
        {
            cipheredText[i] = plaintext[i];
        }
    }

    printf("ciphertext: %s\n", cipheredText);
}