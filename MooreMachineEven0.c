#include <stdio.h>
#include <string.h>

#define MAX 100

// Define states
typedef enum { q0, q1 } State;

// Function to get the next state based on input
void delta(State current_state, char input, State *next_state) {
    switch (current_state) {
        case q0: // Even number of 0's
            if (input == '0') {
                *next_state = q1; // Transition to odd number of 0's
            } else {
                *next_state = q0; // Stay in even state
            }
            break;
        case q1: // Odd number of 0's
            if (input == '0') {
                *next_state = q0; // Transition to even number of 0's
            } else {
                *next_state = q1; // Stay in odd state
            }
            break;
    }
}

// Function to get the output based on the current state
int get_output(State state) {
    switch (state) {
        case q0:
            return 1; // Output for even number of 0's
        case q1:
            return 0; // Output for odd number of 0's
        default:
            return 0; // Default case (shouldn't happen)
    }
}

int main() {
    char input[MAX];
    State current_state = q0; // Initial state is q0 (even number of 0's)
    State next_state;
    
    printf("Enter a string (consisting of only '0' and '1'): ");
    fgets(input, MAX, stdin);
    input[strcspn(input, "\n")] = 0; // Remove newline character if present
    
    for (int i = 0; i < strlen(input); ++i) {
        delta(current_state, input[i], &next_state);
        current_state = next_state;
        printf("Input: %c, Output: %d\n", input[i], get_output(current_state));
    }
    
    // Final output
    printf("Final output: %d\n", get_output(current_state));
    
    return 0;
}
