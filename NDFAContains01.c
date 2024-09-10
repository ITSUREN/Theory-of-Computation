#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX_INPUT_LENGTH 20
#define STATE_COUNT 3

// Define states
typedef enum { q0, q1, q2 } states;
void delta(const bool current_states[], char ch, bool next_states[]);
bool process_input(const char *string);

int main() {
    char string[MAX_INPUT_LENGTH];
    
    printf("Enter a string: ");
    fgets(string, MAX_INPUT_LENGTH, stdin);
    string[strcspn(string, "\n")] = 0;
    
    if (process_input(string)) {
        printf("\nThe string %s is valid.\n", string);
    } else {
        printf("\nThe string %s is not valid.\n", string);
    }
    
    return 0;
}

bool process_input(const char *string) {
    bool current_states[STATE_COUNT] = { true, false, false }; // Start in state q0
    bool next_states[STATE_COUNT] = { false };
    
    int i = 0;
    char ch = string[i];
    
    while (ch != '\0') {
        // Compute the next set of states
        delta(current_states, ch, next_states);

        // Update current states
        for (int j = 0; j < STATE_COUNT; ++j) {
            current_states[j] = next_states[j];
        }
        
        // Clear next_states for the next iteration
        for (int j = 0; j < STATE_COUNT; ++j) {
            next_states[j] = false;
        }
        
        ch = string[++i];
    }

    return current_states[q2];
}

void delta(const bool current_states[], char ch, bool next_states[]) {
    for (int i = 0; i < STATE_COUNT; i++) {
        if (current_states[i]) {
            switch (i) {
                case q0:
                    if (ch == '0') {
                        next_states[q1] = true;
                        next_states[q0] = true;
                    }
                    else if (ch == '1') next_states[q0] = true;
                    break;
                case q1:
                    if (ch == '1') next_states[q2] = true;
                    break;
                case q2:
                    next_states[q2] = true;
                    break;
            }
        }
    }
}