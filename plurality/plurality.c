#include <cs50.h>
#include <stdio.h>
#include <string.h>

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
        printf("Usage: plurality [candidate ...]\n"); // we give candidate names at the command line
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1; // subtract one for the program's name
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1]; // offsetted by one for the program name
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: "); // get name of the candidate to vote for

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
// update vote total of the candidate called
// return true if such candidate exists
// else return false
// assume no two candidates have the same name
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
// basically run a sort to find out the maximum vote number
// we can create a temp array for either bubble or selection sort
// maximum number of ties is 4 if candidates is 9
// i.e. divided by 2
void print_winner(void)
{
    // Selection Sort
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
        // swap the previous min with the new min
        candidate temp = candidates[i];
        candidates[i] = candidates[min];
        candidates[min] = temp;
    }

    // run a while loop to print out the mini
    // number of winners
    int n = candidate_count - 1;
    candidate winner;
    do
    {
        winner = candidates[n];
        n--; // decrement n to get next candidate
        printf("%s\n", winner.name);
    }
    while (candidates[n].votes == winner.votes);
    // repeat while the votes of the next candidate are the same
    return;
}