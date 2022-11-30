#include <stdio.h>
#include <stdlib.h>
  
// Represents a node
typedef struct node
{
    int number;
    struct node *next;
}
node;

int main(void)
{
    // List of size 0
    node *list = NULL;
  
    // Add number to list
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        return 1;
    }
    n->number = 1;
    n->next = NULL;

    // Update list to point to new node
    list = n;
}

// Print numbers
for (node *tmp = list; tmp != NULL; tmp = tmp->next)
{
    printf("%i\n", tmp->number);
}

// Free list
while (list != NULL)
{
    node *tmp = list->next;
    free(list);
    list = tmp;
}
return 0;