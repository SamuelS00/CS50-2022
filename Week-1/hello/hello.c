#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // require the user to enter the name
    string name = get_string("Whas's your name? ");
    printf("hello, %s\n", name);
}