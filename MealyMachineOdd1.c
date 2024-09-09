#include <stdio.h>
#include <string.h>

#define MAX 100

// Define states
typedef enum { q0, q1 } State;

// Function to get the next state and output
void delta(State current_state, char input, State *next_state, int *output) {
    switch (current_state) {
        case q0: // Even number of 1's
            if (input == '1') {
                *next_state = q1; // Transition to odd number of 1's
                *output = 1;
            } else {
                *next_state = q0; // Stay in even state
                *output = 0;
            }
            break;
        case q1: // Odd number of 1's
            if (input == '1') {
                *next_state = q0; // Transition to even number of 1's
                *output = 0;
            } else {
                *next_state = q1; // Stay in odd state
                *output = 1;
            }
            break;
    }
}

int main() {
    char input[MAX];
    State current_state = q0; // Initial state is q0 (even number of 1's)
    State next_state;
    int output;
    
    printf("Enter a string (consisting of only '0' and '1'): ");
    fgets(input, MAX, stdin);
    input[strcspn(input, "\n")] = 0; // Remove newline character if present
    
    for (int i = 0; i < strlen(input); ++i) {
        delta(current_state, input[i], &next_state, &output);
        current_state = next_state;
        printf("Input: %c, Output: %d\n", input[i], output);
    }
    
    // Final output
    printf("Final output: %d\n", output);
    
    return 0;
}
