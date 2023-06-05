#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
// adjacency matrix of graph
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates (strings)
string candidates[MAX];
// pairs of candidates for which one is preffered over the other
pair pairs[MAX * (MAX - 1) / 2];

// number of pairs
int pair_count;
// number of candidates
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        // number of arguments should be at least more than two
        // , first the program name and an array of candidates
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    // -1 for the program name
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    // populate candidates
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
    // for each voter
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        // make a list of ranks equal to number of candidates
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            // ask for the voter's jth rank
            string name = get_string("Rank %i: ", j + 1);

            // if vote can't exist, return error
            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        // if all votes have been casted for the voter,
        // record them
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
            // if name matches a valid candidate
            // update the ranks array
            ranks[rank] = i;
            // return true then
            return true;
        }
    }
    // if no valid cadidate exists return false
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // iterate over the ranks array to get the
    for (int i = 0; i < candidate_count - 1; i++)
    {
        // rank i is preferred all suceeding ranks
        for (int j = i + 1; j < candidate_count; j++)
        {
            // update preferences
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // iterate over pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // if there is a tie, don't add
            // add if i is preffered over j
            if (preferences[i][j] > preferences[j][i])
            {
                // add to pairs
                // printf("%s is preffered over %s\n", candidates[i], candidates[j]);
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                // update pair_count
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // for each pair there is a winner
    // sort in order of the winner
    // selection sort
    // iterate over the pairs
    int max;
    for (int i = 0; i < pair_count - 1; i++)
    {
        // find the largest number in this iteration
        // this is the index of the winner at pair[i]
        max = i;
        for (int j = i + 1; j < pair_count; j++)
        {
            // sort by strength of victory
            if (preferences[pairs[j].winner][pairs[j].loser] > preferences[pairs[max].winner][pairs[max].loser])
            {
                max = j;
            }
        }
        // put max in the ith place
        pair temp = pairs[i];
        pairs[i] = pairs[max];
        pairs[max] = temp;
    }

    // printed sorted array
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // add the first edge
    locked[pairs[0].winner][pairs[0].loser] = true;
    // somehow iterate through the graph
    for (int i = 1; i < pair_count; i++)
    {
        // should the next pair be added ?
        // pair[i].winner is the index of the candidate
        int final_source = pairs[i].winner;
        int final_dest = pairs[i].loser;
        // if there is an edge from this destination, find it
        for (int j = 0; j < candidate_count; j++)
        {
            // if there is an edge in the graph from the dest
            if (locked[final_dest][j])
            {
                // traverse the graph such that we reach the last
                // destination
                final_dest = j;
                if (final_dest == final_source)
                    break;
            }
        }
        // now check if the destination equals the final source
        if (final_source != final_dest)
        {
            // add the edge
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // winner is the source (has no edges pointing to it)
    // lets say we say that a node is the source

    int winner = 0;
    // iterate through the nodes in the graph
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            if (locked[j][winner])
            {
                // if there is an edge, go the next node
                winner = i;
            }
        }
    }

    // print the winner
    printf("%s\n", candidates[winner]);
    return;
}

// helper function to find index of candidate in the candidates array
int get_candidate_index(string candidate)
{
    // iterate over the candidates array
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidate, candidates[i]) == 0)
        {
            return i;
        }
    }
    return -1; // fail indicator
}