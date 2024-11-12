#include <stdio.h>
#include <stdlib.h>

// Function to initialize the first monotonically increasing number
void initialize_monotonic(int *arr, int length) {
    for (int i = 0; i < length; i++) {
        arr[i] = 0;
    }
}

// Function to increment a monotonically increasing array
int increment_monotonic(int *arr, int length, int base) {
    for (int i = length - 1; i >= 0; i--) {
        if (arr[i] < base - 1) {
            arr[i]++;
            // Ensure all subsequent digits are >= the previous one
            for (int j = i + 1; j < length; j++) {
                arr[j] = arr[i];
            }
            return 1;  // Successfully incremented
        }
    }
    return 0;  // Reached the end
}

// Function to compute binomial coefficient (n choose k) efficiently
unsigned long long binomial_coefficient(int n, int k) {
    if (k > n) {
        return 0;
    }
    if (k == 0 || k == n) {
        return 1;
    }

    unsigned long long result = 1;
    
    // Since C(n, k) = C(n, n-k), we take the smaller value of k to optimize
    if (k > n - k) {
        k = n - k;
    }

    // Calculate the binomial coefficient using the formula
    // C(n, k) = n * (n - 1) * ... * (n - k + 1) / k!
    for (int i = 0; i < k; i++) {
        result *= (n - i);
        result /= (i + 1);
    }

    return result;
}

// Function to compute the stars and bars result
unsigned long long stars_and_bars(int N, int M) {
    // Use the formula: (N + M - 1) choose M
    return binomial_coefficient(N + M - 1, M);
}

int main() {
    int base = 10;    // Set your desired base here (e.g., 3 for 0,1,2)
    int length = 20;  // Set your desired length here (e.g., 5 digits)

    // Initialize the number array
    int number[5];
    initialize_monotonic(number, length);

    // Print the first number
    int i = 1;
    // Continue incrementing and printing until no more numbers
    while (increment_monotonic(number, length, base)) {
        i++;
    }

    unsigned long long result = stars_and_bars(base, length);
    printf("There are %i ways to assemble the results\n", i);
    printf("The Stars And Bars calculation gives %llu ways\n",result);

    return 0;
}
