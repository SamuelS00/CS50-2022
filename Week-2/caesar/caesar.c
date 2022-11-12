#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

bool only_digits(string key);
char rotate(char c, int n);

int main(int argc, string argv[])
{
    // checks if there are two arguments in argv
    // checks if argv[1] is number
    if (argc != 2 || only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // request string for user
    string plaintext = get_string("plaintext: ");
    // variable save text size passed by user
    int plaintext_length = strlen(plaintext);
    // variable sabe key passed by user
    int key = atoi(argv[1]);
    // create string the size of plaintext
    char ciphertext[plaintext_length];

    // iterates through each position of the string by calling a specific function for each position
    for (int i = 0; i <= plaintext_length; i++)
    {
        char letter_rotated = rotate(plaintext[i], key);
        // in each position i store the new character
        ciphertext[i] = letter_rotated;
    }

    // print ciphertext
    printf("ciphertext: %s\n", ciphertext);
    return 0;
}

// rotates letters based on their position in the ascii table
char rotate(char c, int n)
{
    int MIN_UPPER_CAP = 65;
    int MIN_LOWER_CAP = 97;

    // create index alphabet
    string ALPHABET_INDEX = "abcdefghijklmnopqrstuvwxyz";

    // checks for lower if so returns letter based on alphabetical position index
    if (islower(c))
    {
        int char_code = c;
        int pos = char_code - MIN_LOWER_CAP;
        int key = (pos + n) % 26;

        return ALPHABET_INDEX[key];
    }

    // checks for upper if so returns letter based on alphabetical position index
    if (isupper(c))
    {
        int char_code = c;
        int pos = char_code - MIN_UPPER_CAP;
        int key = (pos + n) % 26;

        return toupper(ALPHABET_INDEX[key]);
    }

    // if not a letter it is returned without modification
    return c;
}

// function that checks if it is a digit
bool only_digits(string key)
{
    int count = 0;
    bool isDigit;

    for (int i = 0; i < strlen(key); i++)
    {
        if (isdigit(key[i]))
        {
            count++;
        }
    }

    isDigit = count == strlen(key);
    return !isDigit;
}
