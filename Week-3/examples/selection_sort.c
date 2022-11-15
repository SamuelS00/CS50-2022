#include <cs50.h>
#include <stdio.h>
#include <string.h>

// 
int main(void)
{
    int list_values[] = {7, 5, 1, 8, 3, 2};
    int list_length = 5;

    for (int i = 0; i <= list_length - 1; i++)
    {
        int min_index = i;

        for (int j = i; j <= list_length - 1; j++)
        {
            if (list_values[j] < list_values[min_index])
            {
                min_index = j;
            }
        }

        if (list_values[i] > list_values[min_index])
        {
            int aux = list_values[i];
            list_values[i] = list_values[min_index];
            list_values[min_index] = aux; 
        }
        printf("Number: %i\n", list_values[i]);
    }
}