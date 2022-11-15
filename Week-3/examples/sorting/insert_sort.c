#include <cs50.h>
#include <stdio.h>


void insertSort(int arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
           
        arr[j + 1] = key;
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

    insertSort(list_values, n);

    printf("sorted arr: ");
    printArr(list_values, n);

    return 0;
}