#include <stdio.h>

#define MAX_CANDIDATES 13

typedef struct {
    int id;
    int votes;
} Candidate;

int main(void) {
    int num_candidates = 3;
    int ballots[] = {3, 1, 2, 3, 1, 0, 3, 1, 2, 3, 1, 2, 3, 1, 2, 9};
    int total_ballots = sizeof(ballots) / sizeof(ballots[0]);

    int votes[MAX_CANDIDATES] = {0};
    int valid_votes = 0, invalid_votes = 0;

    for (int i = 0; i < total_ballots; i++) {
        int v = ballots[i];
        if (v >= 1 && v <= num_candidates) {
            votes[v]++;
            valid_votes++;
        } else {
            invalid_votes++;
        }
    }

    Candidate sorted[MAX_CANDIDATES];
    for (int c = 1; c <= num_candidates; c++) {
        sorted[c - 1].id = c;
        sorted[c - 1].votes = votes[c];
    }

    for (int i = 0; i < num_candidates - 1; i++) {
        for (int j = 0; j < num_candidates - 1 - i; j++) {
            if (sorted[j].votes < sorted[j + 1].votes) {
                Candidate tmp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = tmp;
            }
        }
    }

    printf("Valid Votes: %d | Invalid Votes: %d\n", valid_votes, invalid_votes);
    for (int i = 0; i < num_candidates; i++) {
        printf("Rank %d: Candidate #%d - %d votes\n", i + 1, sorted[i].id, sorted[i].votes);
    }

    if (num_candidates > 1 && sorted[0].votes == sorted[1].votes) {
        printf("Result: TIE between Candidate #%d and Candidate #%d (%d votes each)\n",
               sorted[0].id, sorted[1].id, sorted[0].votes);
    } else {
        printf("Result: Winner is Candidate #%d (%d votes)\n", sorted[0].id, sorted[0].votes);
    }

    return 0;
}
