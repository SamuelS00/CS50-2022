#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int heigth;

    // requests a valid number for the user
    do
    {
        heigth = get_int("enter a number between 1 and 8: ");
    }
    while (heigth < 1 || heigth > 8);


    for (int i = 0; i < heigth; i++)
    {
        // opposite opposite of index
        int opposite = heigth - i - 1;
        for (int j = 0; j < heigth; j++)
        {
            // compare opposite with row
            if (opposite <= j)
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
}