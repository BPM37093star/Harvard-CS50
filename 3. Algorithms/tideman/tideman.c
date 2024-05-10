#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

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
bool is_cyclic(int current, bool visited[], bool rec_stack[]);

int main(int argc, string argv[])
{
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
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

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
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            for (int j = 0; j < rank; j++)
            {
                if (ranks[j] == i)
                {
                    printf("Invalid vote: Candidate %s is already voted.\n", name);
                    return false;
                }
            }
            ranks[rank] = i;
            return true;
        }
    }
    printf("Invalid vote: Candidate %s not found.\n", name);
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            int preferred_candidate = ranks[i];
            int less_preferred_candidate = ranks[j];
            preferences[preferred_candidate][less_preferred_candidate]++;
        }

    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    pair_count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            int preference_i_j = preferences[i][j];
            int preference_j_i = preferences[j][i];
            if (preference_i_j > preference_j_i)
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preference_j_i > preference_i_j)
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
         }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    pair temp;
    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = 0; j < pair_count - 1 - i; j++)
        {
            int strength_i = preferences[pairs[j].winner][pairs[j].loser];
            int strength_next = preferences[pairs[j + 1].winner][pairs[j + 1].loser];
            if (strength_i < strength_next)
            {
                temp = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp;
            }
        }
    }
    return;
}
bool is_cyclic(int current, bool visited[], bool rec_stack[])
{
    if(!visited[current])
    {
        visited[current] = true;
        rec_stack[current] = true;

        for (int i = 0; i < candidate_count; i++)
        {
            if (locked[current][i] && !visited[i] && is_cyclic(i, visited, rec_stack))
            {
                return true;
            }
            else if(rec_stack[i])
            {
                return true;
            }
        }
    }
    rec_stack[current] = false;
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    /*
    bool visited[MAX];
    bool rec_stack[MAX];

    for (int i = 0; i < pair_count; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;
        if (is_cyclic(pairs[i].winner, visited, rec_stack))
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
    }
    return;
    */
    bool visited[MAX];
    bool rec_stack[MAX];
    for (int i = 0; i < pair_count; i++)
    {
        // Assume the pair is non-cyclical
        locked[pairs[i].winner][pairs[i].loser] = true;

        // Check for cycles after locking the pair
        if (is_cyclic(pairs[i].winner, visited, rec_stack))
        {
            // If a cycle is detected, unlock the pair
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        bool is_winner = true;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                is_winner = false;
                break;
            }
        }
        if (is_winner)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
}
