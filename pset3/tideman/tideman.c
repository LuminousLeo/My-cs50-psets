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
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];    //36

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
bool cycle_check(int pairs_winner, int pairs_loser);
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
            ranks[rank] = i;    //ranks[0] = is the person that i is at, i = 1, alex mason then rank[0] = mason
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)   //i think the loop breaks at the candidate placed in the last rank
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;  //preferences[alex]over[mason]
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
            if (preferences[i][j] > preferences[j][i]) //if the peaple who prefer a over b is bigger than the peaple who prefer b over a
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i]) //if a over b is lesser than b over a
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
    //usage of bubble sort
    for (int i = pair_count - 1; i >= 0; i--)   //because it is decreasing order i = pair_count and >= 0 because it is an array
    {
        for (int j = 0; j < i; j++) //checks each pair to see strengh of victory
        {
            if (preferences[pairs[j].winner][pairs[j].loser] < preferences[pairs[i].winner][pairs[i].loser])
            {
                //if so, swap pairs[j] with pairs[i]
                pair temp = pairs[j];
                pairs[j] = pairs[i];
                pairs[i] = temp;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    //iterate through sorted pairs
    for (int i = 0; i < pair_count; i++)
    {
        //check if locking the current pair would create a cycle
        if (!cycle_check(pairs[i].winner, pairs[i].loser))  //same as saying cycle_check(x, y) == false
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}


//helper function to see when the cycle breaks
bool cycle_check(int pairs_winner, int pairs_loser)
{
    //if it is the last candidate it does not create a cycle
    if (pairs_winner == pairs_loser)
    {
        return true;
    }

    //recursevaly check all candidates that the current candidate is locked in with
    for (int i = 0; i < candidate_count; i++)
    {
        //if there is a cycle
        if (locked[i][pairs_winner] == true && cycle_check(i, pairs_loser) == true) //same as saying locked[pairs_winner][i] and recursion
        {
            return true;
        }
    }

    //if there is no cycle
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)   //take a candidate eg: candidates[0] = alice
    {
        int not_locked = 0;

        for (int j = 0; j < candidate_count; j++)   //now recursively check if any candidate is locked in with alice
        {
            if (locked[j][i] == false)
            {
                not_locked++;
                if (not_locked == candidate_count)
                {
                    //if no one is lockd in with alice than alice is the source of the graph
                    printf("%s\n", candidates[i]);  //print winner of the election
                }
            }
        }
    }

    return;
}