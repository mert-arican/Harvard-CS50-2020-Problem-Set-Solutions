//
//  Tideman.c
//  Problem Set 3
//
//  Created by Mert Arıcan on 14.10.2019.
//  Copyright © 2019 Mert Arıcan. All rights reserved.
//

#include <stdio.h>
#include <stdbool.h>
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
char *candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, char *name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, char *argv[])
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
            preferences[i][j] = 0;
        }
    }

    pair_count = 0;
    printf("Number of voters: ");
    int voter_count;
    scanf("%i", &voter_count);
    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];
        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            char name[100];
            printf("Rank %i: ", j + 1);
            scanf("%s", name);
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
bool vote(int rank, char *name, int ranks[])
{
    int index = 0;
    bool result = false;
    for (int i = 0; i < candidate_count; i++) {
        if (strcasecmp(candidates[i], name) == 0) {
            result = true; index = i;
        }
    }
    if (!result) { return false; }
    ranks[rank] = index;
    return true;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count-1; i++) {
        int winner = ranks[i];
        for (int k = i+1; k < candidate_count; k++) {
            int loser = ranks[k];
            preferences[winner][loser] += 1;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int count = 0;
    for (int i = 0; i < candidate_count; i++) {
        for (int j = i; j < candidate_count; j++) {
            if (i != j) {
                pair p;
                if (preferences[i][j] > preferences[j][i]) {
                    p.winner = i ; p.loser = j;
                    pairs[count] = p; count++;
                    pair_count++;
                } else if (preferences[i][j] < preferences[j][i]) {
                    p.winner = j ; p.loser = i;
                    pairs[count] = p; count++;
                    pair_count++;
                }
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count; i++) {
        int first = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
        for (int j = 0; j < pair_count; j++) {
            int second = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner];
            if (first < second) {
                pair te = pairs[j];
                pairs[j] = pairs[i];
                pairs[i] = te;
            }
        }
    }
    for (int i = 0; i < pair_count / 2; i++) {
        pair temp = pairs[i];
        pairs[i] = pairs[pair_count-1-i];
        pairs[pair_count-1-i] = temp;
    }
    for (int i = 0; i < pair_count; i++) {
        printf("winner: %s, loser: %s, score1: %d, score2: %d \n", candidates[pairs[i].winner], candidates[pairs[i].loser], preferences[pairs[i].winner][pairs[i].loser], preferences[pairs[i].loser][pairs[i].winner]);
    }
    return;
}

bool createsCycle(int loser, int winner) {
    for (int i = 0; i < candidate_count; i++) {
        if (locked[loser][i] == 1 && loser != i) {
            if (i == winner) {
                return true;
            } else {
                return createsCycle(i, winner);
            }
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++) {
        if (!createsCycle(pairs[i].loser, pairs[i].winner)) {
            locked[pairs[i].winner][pairs[i].loser] = 1;
        }
    }
    return;
}

bool hasSource(int j) {
    for (int i = 0; i < candidate_count; i++) {
        if (locked[i][j]) {
            return true;
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++) {
        if (!hasSource(i)) {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}
