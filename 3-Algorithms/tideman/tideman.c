#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Defines 'string' as a data type
typedef char *string; 

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(void)
{
    string argv[] = {"tideman.c", "aa", "bb", "cc"};
    int argc = sizeof(argv)/sizeof(argv[0]);
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    // Prompting and getting the number of voters
    int voter_count = 0;
    printf("Number of voters: ");
    scanf("%d", &voter_count);

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            // Prompting and getting the name of candidate
            char name[50] = "";
            printf("Rank %i: ", j + 1);
            scanf("%s", &name);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        } 
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    int ranks_size = candidate_count;
    
    for (int i = 0; i < ranks_size; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (ranks[i] == j)
            {
                for (int f = i + 1; f < ranks_size; f++)
                {
                    preferences[j][ranks[f]]++;
                }
            }
        }
    }     
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i <= candidate_count; i++)
    {
        for (int j = 0; j <= candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[i].winner = i;
                pairs[i].loser = j;
                pair_count++;
            }
            if (preferences[j][i] > preferences[i][j])
            {
                pairs[i].winner = j;
                pairs[i].loser = i;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // initialazing new empty arry for the sorted pairs 
    pair new_pairs[MAX * (MAX - 1) / 2];
    
    // Sortign the pairs using Bubble Sort algorithm to sort the pairs
    int swap_count = -1; // setting it to non zero int
    do
    {
        swap_count = 0; // setting swap count to zero

        // iterate over the unsorted pairs and bubble sort the candidates with the must vots to the right side 
        for (int i = 0; i < pair_count; i++)
        {
            if ((preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[i+1].winner][pairs[i+1].loser]) && i+1 < pair_count)
            {
                new_pairs[i] = pairs[i+1];
                new_pairs[i+1] =  pairs[i];

                // Replacing the old pairs array with the new sorted one  
                pairs[i] = new_pairs[i];
                pairs[i+1] = new_pairs[i+1];
                swap_count++;
            }
        }
    }
    while (swap_count != 0);

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if ((pairs[i].loser != pairs[pair_count-1].winner) || (pairs[0].winner != pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        int arrows = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (!locked[j][i])
            {
                arrows++;
            }
        }
        if (arrows == candidate_count)
        {
            printf("%s\n", candidates[i]);
            return;
        }
        arrows = 0;
    }
    return;
}
