#include <cs50.h>
#include <stdio.h>


void bubblesort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void printArr(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf(" %d ", arr[i]);
    }
}

 
int main(void)
{
    int list_values[5] = {7, 5, 1, 8, 3};
    int n = sizeof(list_values) / sizeof(list_values[0]);
    
    printf("unordered array: ");
    printArr(list_values, n);

    bubblesort(list_values, n);

    printf("sorted arr: ");
    printArr(list_values, n);
    return 0;
}