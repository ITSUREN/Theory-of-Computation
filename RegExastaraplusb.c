#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_INPUT_LENGTH 100
#define NUM_STATES 3

// NFA State definition and function prototyping
typedef enum { q0, q1, qf } state;
void delta(state *current_states, int *num_current, char ch, state *next_states, int *num_next);
void add_state(state *states, int *number_of_states, state s);
bool is_state_in_set(state *states, int num_states, state s);
bool matches_regex(const char *string);

int main() {
    char string[MAX_INPUT_LENGTH];

    printf("Enter a string: ");
    fgets(string, MAX_INPUT_LENGTH, stdin);
    string[strcspn(string, "\n")] = 0;  // Remove newline character from input

    if (matches_regex(string)) {
        printf("The string \"%s\" matches the regex a*(a+b).\n", string);
    } else {
        printf("The string \"%s\" does not match the regex a*(a+b).\n", string);
    }
    return 0;
}

void delta(state *current_states, int *num_current, char ch, state *next_states, int *num_next) {
    *num_next = 0;  // Reset next state count
    for (int i = 0; i < *num_current; ++i) {
        switch (current_states[i]) {
            case q0:
                if (ch == 'a') {
                    add_state(next_states, num_next, q0);
                    add_state(next_states, num_next, q1);  
                } else if (ch == 'b') {
                    add_state(next_states, num_next, q1);  
                }
                break;
            case q1:
                add_state(next_states, num_next, qf); 
                break;
            case qf:
                // qf is the final state, no further transitions should occur
                return;
        }
    }
}

bool matches_regex(const char *string) {
    state current_states[NUM_STATES], next_states[NUM_STATES];
    int num_current = 0, num_next = 0;

    // Start with state q0
    add_state(current_states, &num_current, q0);
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

void add_state(state *states, int *number_of_states, state s) {
    for (int i = 0; i < *number_of_states; ++i) {
        if (states[i] == s) return;  // Already in the set
    }
    states[(*number_of_states)++] = s;  // Add the state to the set
}

bool is_state_in_set(state *states, int num_states, state s) {
    for (int i = 0; i < num_states; ++i) {
        if (states[i] == s) return true;
    }
    return false;
}