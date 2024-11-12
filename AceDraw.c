#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to perform Fisher-Yates shuffle on the deck
void shuffle(char *deck, int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

// Function to simulate N card draws and count M times where exactly 2 aces are drawn
int simulate_card_draws(int N) {
    // Initialize deck: 4 aces ('A') and 48 non-aces ('N')
    char deck[52];
    for (int i = 0; i < 4; i++) {
        deck[i] = 'A';
    }
    for (int i = 4; i < 52; i++) {
        deck[i] = 'N';
    }

    int M = 0;  // Counter for how many times exactly 2 aces are drawn
    int milestone = N / 10;  // 10% milestone for progress

    // Simulate N draws
    for (int i = 0; i < N; i++) {
        shuffle(deck, 52);  // Shuffle the deck

        // Count aces in the first 4 drawn cards
        int ace_count = 0;
        for (int j = 0; j < 4; j++) {
            if (deck[j] == 'A') {
                ace_count++;
            }
        }

        // If exactly 2 aces were drawn, increment the counter
        if (ace_count == 2) {
            M++;
        }

        // Output progress at every 10% completion
        if ((i + 1) % milestone == 0) {
            printf("%d%% complete\n", ((i + 1) / milestone) * 10);
        }
    }

    return M;
}

int main() {
    srand(time(NULL));  // Seed the random number generator

    int N = 10000000;  // Number of simulations
    int M = simulate_card_draws(N);

    printf("In %d simulations, exactly 2 aces were drawn %d times for a probability of %.5f\n", N, M, (((double) M) / N));

    return 0;
}
