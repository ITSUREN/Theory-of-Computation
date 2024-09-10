#include <stdio.h>
#include <string.h>

#define MAX_INPUT_LENGTH 100

// Define states and transition function
typedef enum { q0, q1 } State;
void delta(State, char, State *, int *);

int main() {
    char input[MAX_INPUT_LENGTH];
    State current_state = q0; State next_state;
    int output;
    
    printf("\nEnter a binary string: ");
    fgets(input, MAX_INPUT_LENGTH, stdin);
    input[strcspn(input, "\n")] = 0;
    
    for (int i = 0; i < strlen(input); ++i) {
        delta(current_state, input[i], &next_state, &output);
        current_state = next_state;
        printf("Input: %c, Output: %d\n", input[i], output);
    }
    
    printf("Final output: %d\n", output);
    return 0;
}

void delta(State current_state, char input, State *next_state, int *output) {
    switch (current_state) {
        case q0:
            if (input == '1') {
                *next_state = q1;
                *output = 1;
            } else {
                *next_state = q0;
                *output = 0;
            }
            break;
        case q1:
            if (input == '1') {
                *next_state = q0;
                *output = 0;
            } else {
                *next_state = q1;
                *output = 1;
            }
            break;
    }
}