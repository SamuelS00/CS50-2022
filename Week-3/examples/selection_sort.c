#include <cs50.h>
#include <stdio.h>
 
void selectionSort(int arr[], int n)
{
    for (int i = 0; i <= n - 1; i++)
    {
        int min_index = i;

        for (int j = i; j <= n - 1; j++)
        {
            if (arr[j] < arr[min_index])
            {
                min_index = j;
            }
        }

        if (arr[i] > arr[min_index])
        {
            int aux = arr[i];
            arr[i] = arr[min_index];
            arr[min_index] = aux; 
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
    int list_values[] = {7, 5, 1, 8, 3, 2};
    int n = sizeof(list_values) / sizeof(list_values[0]);

    printf("unordered array: ");
    printArr(list_values, n);

    selectionSort(list_values, n);

    printf("sorted arr: ");
    printArr(list_values, n);
    return 0;
}