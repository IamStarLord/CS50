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
        // the voter i records candidate with "name"
        // for rank j
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            // for voter i to candidate j
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
        // look at each voters top candidate which hasn't yet been eliminated
        tabulate();

        // Check if election has been won
        // print_winner prints the winner as well as returns a bool
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        // find the last place candidate
        int min = find_min();
        // if everyone in the election is a tie with the same number of voters
        bool tie = is_tie(min);

        // If tie, everyone wins
        // if no candidate is being eliminated, make everyone win
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
        // otherwise eliminate the last place candidate
        eliminate(min);

        // Reset vote counts back to zero
        // why ?
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
// if name is valid candidate
// update the preference array with the corresponding candidate's rank
// voter i, rank j, string name
bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            // if candidate exists then update the preferences array
            // [i][i] voter i's preference j corresponding to the index
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
// check if the candidate has been eliminated
// if not then update the vote count
// else move on to the next
void tabulate(void)
{
    int candidate;
    // iterate through the preferences array
    // for each voter
    for (int i = 0; i < voter_count; i++)
    {
        // look into the first preference at the start of the loop
        int j = 0;
        while (true)
        {
            candidate = preferences[i][j];
            // check if the candidate at jth preference is eliminated
            if (candidates[candidate].eliminated)
            {
                // look for the next preference
                j++;
                continue;
            }
            // else if the candidate is not eliminated
            // increment the voter count
            candidates[candidate].votes += 1;
            // break from loop and move on to the next voter
            break;
        }
    }
    return;
}

// Print the winner of the election, if there is one
// If candidate has more than half the votes in the ballot
// their name should be printed and function should return true
// if no one has won yet, return false
bool print_winner(void)
{
    int majority = (voter_count / 2) + 1;
    // iterate over the candidates array
    for (int i = 0; i < candidate_count; i++)
    {
        // if any candidate has a mojority
        if (candidates[i].votes >= majority)
        {
            // print their name
            printf("%s\n", candidates[i].name);
            // return true
            return true;
        }
    }
    // else if no one has won
    return false;
}

// Return the minimum number of votes any remaining candidate has
// find the minimum and return it if the candidate has not been eliminated
int find_min(void)
{
    // select min to be the first element of the array
    int min;

    // run a loop in a loop
    for (int i = 0; i < candidate_count; i++)
    {
        // set an initial minimum
        min = i;
        // run this loop to find the smallest number
        for (int j = i; j < candidate_count; j++)
        {
            if (candidates[j].votes < candidates[min].votes)
            {
                min = j;
            }
        }
        // if candidate has not been eliminated then break out and return
        if (!candidates[min].eliminated)
        {
            break;
        }
        // if the candidate has already been eliminated then swap it with the ith candidate
        candidate temp = candidates[i];
        candidates[i] = candidates[min]; // we don't want this
        candidates[min] = temp; // we do want this
    }
    return candidates[min].votes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // iterate through the loop
    for (int i = 0; i < candidate_count; i++)
    {
        // if any candidate who is not yet eliminated
        // has unequal votes then return false
        if (candidates[i].votes != min && !(candidates[i].eliminated))
        {
            return false;
        }
    }
    // otherwise it is a tie
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // iterate through the candidates array
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min && !(candidates[i].eliminated))
        {
            // eliminate the candidate
            candidates[i].eliminated = true;
        }
    }
    return;
}