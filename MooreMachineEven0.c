#include <stdio.h>
#include <string.h>

#define MAX_INPUT_LENGTH 100

// Define states and transition function prototyping
typedef enum { q0, q1 } State;
void delta(State current_state, char input, State *next_state);
int get_output(State state);

int main() {
    char input[MAX_INPUT_LENGTH];
    State current_state = q0;
    State next_state;
    
    printf("\nEnter a binary string: ");
    fgets(input, MAX_INPUT_LENGTH, stdin);
    input[strcspn(input, "\n")] = 0;
    
    for (int i = 0; i < strlen(input); ++i) {
        delta(current_state, input[i], &next_state);
        current_state = next_state;
        printf("Input: %c, Output: %d\n", input[i], get_output(current_state));
    }
    
    printf("Final output: %d\n", get_output(current_state));
    return 0;
}

void delta(State current_state, char input, State *next_state) {
    switch (current_state) {
        case q0: 
            if (input == '0') 
                *next_state = q1; 
            else 
                *next_state = q0; 
            break;
        case q1: 
            if (input == '0') 
                *next_state = q0; 
            else 
                *next_state = q1;
            break;
    }
}

int get_output(State state) {
    switch (state) {
        case q0: return 1; 
        case q1: return 0; 
        default: return 0;
    }
}