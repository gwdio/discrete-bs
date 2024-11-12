import numpy as np
from collections import Counter

# Function to simulate drawing 4 cards at random N times and counting M where exactly 2 aces are drawn
def simulate_card_draws(N):
    # Total deck (4 aces, 48 non-aces)
    deck = ['ace'] * 4 + ['non-ace'] * 48
    M = 0  # Counter for how many times exactly 2 aces are drawn

    # Simulate drawing 4 cards N times
    for _ in range(N):
        # Randomly draw 4 cards
        draw = np.random.choice(deck, size=4, replace=False)
        # Count how many aces were drawn
        counts = Counter(draw)
        if counts['ace'] == 2:
            M += 1

    return M

# Example usage
N = 1000000  # Number of simulations
M = simulate_card_draws(N)

print(M)
print((M/N))
