#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX 100
#define NUM_STATES 3

// Define the states for the NFA
typedef enum { q0, q1, qf } state;

// Adds a state to the set of states (active states)
void add_state(state *states, int *number_of_states, state s) {
    for (int i = 0; i < *number_of_states; ++i) {
        if (states[i] == s) return;  // Already in the set
    }
    states[(*number_of_states)++] = s;  // Add the state to the set
}

// Transition function that takes the current set of states and a character
void delta(state *current_states, int *num_current, char ch, state *next_states, int *num_next) {
    *num_next = 0;  // Reset next state count
    for (int i = 0; i < *num_current; ++i) {
        switch (current_states[i]) {
            case q0:
                if (ch == 'a') {
                    add_state(next_states, num_next, q0);  // Loop in q0 for 'a'
                    add_state(next_states, num_next, q1);  // Can also move to q1 on 'a'
                } else if (ch == 'b') {
                    add_state(next_states, num_next, q1);  // Move to q1 on 'b'
                }
                break;
            case q1:
                add_state(next_states, num_next, qf);  // Move to qf for any 'a' or 'b'
                break;
            case qf:
                // qf is the final state, no further transitions should occur
                return;
        }
    }
}

// Function to check if a state is in the set of active states
bool is_state_in_set(state *states, int num_states, state s) {
    for (int i = 0; i < num_states; ++i) {
        if (states[i] == s) return true;
    }
    return false;
}

// Function to check if the string matches the regex a*(a+b)
bool matches_regex(const char *string) {
    state current_states[NUM_STATES], next_states[NUM_STATES];
    int num_current = 0, num_next = 0;

    // Start with state q0
    add_state(current_states, &num_current, q0);

    // Process each character in the string
    for (int i = 0; string[i] != '\0'; ++i) {
        char ch = string[i];
        delta(current_states, &num_current, ch, next_states, &num_next);

        // Move to the next set of states
        memcpy(current_states, next_states, sizeof(state) * num_next);
        num_current = num_next;

        // If no valid transitions, reject the string
        if (num_current == 0) return false;
    }

    // Accept only if we end in state q1 (a valid final state)
    return is_state_in_set(current_states, num_current, q1);
}

int main() {
    char string[MAX];

    printf("Enter a string: ");
    fgets(string, MAX, stdin);
    string[strcspn(string, "\n")] = 0;  // Remove newline character from input

    if (matches_regex(string)) {
        printf("The string \"%s\" matches the regex a*(a+b).\n", string);
    } else {
        printf("The string \"%s\" does not match the regex a*(a+b).\n", string);
    }

    return 0;
}
