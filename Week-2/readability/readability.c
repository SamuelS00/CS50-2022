#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
float average_number(float qtd_words, float qtd);
int indice_coleman_liau(float L, float S);

int main(void)
{
    // here I request a text for the user
    string text = get_string("Text: ");

    // here I count the letters, words and sentences of the text passed by the user
    int number_of_letters = count_letters(text);
    int number_of_words = count_words(text);
    int number_of_sentences = count_sentences(text);

    // here I average letters and sentences for every 100 words
    // I cast integer parameters to float
    float L = average_number(number_of_words, number_of_letters);
    float S = average_number(number_of_words, number_of_sentences);

    // using coleman liau`s formula to find reading level of the text using tge varibles calculated above
    // the returned value will be rounded to the nearest integer
    int index = indice_coleman_liau(L, S);

    // here I check if the reading level is less than 1 and greater than 16, if it is, it will have a specific return
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }

    if (index > 15)
    {
        printf("Grade 16+\n");
    }

    // if in the range 1 to 16 return the calculated reading level
    if (index > 1 && index < 16)
    {
        printf("Grade %i\n", index);
    }
}

int count_letters(string text)
{
    // get the full length of the text
    int string_len = strlen(text);
    int count = 0;

    //I go through each position of the string checking if it is an alpha ( a-z or A-Z )
    // if it is the counter is incremented by one.
    for (int i = 0; i < string_len; i++)
    {
        // here I use the isalpha method of the string library to check if it is a alpha
        if (isalpha(text[i]))
        {
            count++;
        }
    }

    return count;
}

int count_words(string text)
{
    // get the full length of the text
    int string_len = strlen(text);
    // there will be at least one word
    // and it is necessary because I cannot count one more space after the last word of the text.
    int count = 1;

    // I go through each position of the string checking if it is a space
    // I deduce that each space serves to separate each word of a sentence.
    // if it is a space the counter is incremented by one.
    for (int i = 0; i < string_len; i++)
    {
        // here I use the isspace method of the ctype library to check if it is a space
        if (isspace(text[i]))
        {
            count++;
        }
    }

    return count;
}

int count_sentences(string text)
{
    int string_len = strlen(text);
    int count = 0;

    for (int i = 0; i < string_len; i++)
    {
        // here I check each character, if any character is equal to the special characters "?", ".", "!"
        // the counter is incremented by one
        // but I need to cast the characters to an integer and match them by their representation in the ASCII table.
        if ((int) text[i] == 33 || (int) text[i] == 46 || (int) text[i] == 63)
        {
            count++;
        }
    }

    return count;
}

// the function has responsability of calculating the averages of both letters and sentences per 100 words.
float average_number(float qtd_words, float qtd)
{
    float average = qtd / qtd_words * 100;
    return average;
}

// the function has responsability to calculate the coleman liau index.
int indice_coleman_liau(float L, float S)
{
    float index = 0.0588 * L - 0.296 * S - 15.8;
    return round(index);
}