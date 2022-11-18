#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes += 1;
            return true;
        }
    }

    return false;
}

void merge(candidate *arr, int start, int mid, int end)
{
    int i, j, k;
    int n1 = mid - start + 1;
    int n2 = end - mid;

    // create temporary arrays
    candidate L[n1], R[n2];

    // copy the halves of the array to the temporary arrays
    for (i = 0; i < n1; i++)
    {
        L[i] = arr[start + i];
    }
    for (j = 0; j < n2; j++)
    {
        R[j] = arr[mid + 1 + j];
    }

    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = start; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i].votes >= R[j].votes)
        {
            arr[k] = L[i];
            i += 1;
        }
        else
        {
            arr[k] = R[j];
            j += 1;
        }
        k += 1;
    }

    // copies the rest of the left half elements
    while (i < n1)
    {
        arr[k] = L[i];
        i += 1;
        k += 1;
    }

    // copies the rest of the left half elements
    while (j < n2)
    {
        arr[k] = R[j];
        j += 1;
        k += 1;
    }
}

void mergeSort(candidate *arr, int start, int end)
{
    if (start < end)
    {
        // index that is in the middle of the sum
        int mid = start + (end - start) / 2;

        // Sort first and second halves
        mergeSort(arr, start, mid);
        mergeSort(arr, mid + 1, end);

        merge(arr, start, mid, end);
    }
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    mergeSort(candidates, 0, candidate_count - 1);

    int count = 1;

    // checks if there is any candidate with the same number of votes as the candidate with the most votes
    // if it has any count it is incremented to be used as index to stop the loop that prints the names
    for (int i = 0; i < candidate_count - 1; i++)
    {
        if (candidates[0].votes == candidates[i + 1].votes)
        {
            count++;
        }
    }

    // print the names up to count
    for (int i = 0; i < count; i++)
    {
        printf("%s\n", candidates[i].name);
    }
}