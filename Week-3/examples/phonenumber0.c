#include <cs50.h>
#include <stdio.h>
#include <string.h>
  
// This program is correct,
// but not well-designed since we’ll have to maintain both arrays carefully to make sure that the names and numbers line up.

int main(void)
{
    string names[] = {"Carter", "David"};
    string numbers[] = {"+1-617-495-1000", "+1-949-468-2750"};
  
    for (int i = 0; i < 2; i++)
    {
        if (strcmp(names[i], "David") == 0)
        {
            printf("Found %s\n", numbers[i]);
            return 0;
        }
    }
    printf("Not found\n");
    return 1;
}