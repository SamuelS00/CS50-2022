#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }

    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    for (int i = 0; i < voter_count; i++)
    {
        if (!candidates[preferences[i][0]].eliminated)
        {
            candidates[preferences[i][0]].votes += 1;
        }
        else if (!candidates[preferences[i][1]].eliminated)
        {
            candidates[preferences[i][1]].votes += 1;
        }
        else
        {
            candidates[preferences[i][2]].votes += 1;
        }
    }

    return;
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

// Print the winner of the election, if there is one
bool print_winner(void)
{
    int majority = (voter_count / 2) + 1;
    candidate sorted_candidates[MAX_CANDIDATES];

    for (int i = 0; i < candidate_count; i++)
    {
        sorted_candidates[i] = candidates[i];
    }

    mergeSort(sorted_candidates, 0, candidate_count - 1);

    if (sorted_candidates[0].votes >= majority)
    {
        printf("%s\n", sorted_candidates[0].name);
        return true;
    }

    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min_vote = voter_count;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes < min_vote && !candidates[i].eliminated)
        {
            min_vote = candidates[i].votes;
        }
    }

    return min_vote;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false && candidates[i].votes != min)
        {
            return false;
        }
    }

    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }

    return;
}