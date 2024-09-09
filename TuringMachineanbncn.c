#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_TAPE_LENGTH 100

typedef enum {
    q0, q1, q2, q3, q4, q5
} State;

void initialize_tape(char tape[], const char *input);
void print_tape(char tape[], int head_position);
bool turing_machine(char tape[], int tape_length);

int main() {
    char tape[MAX_TAPE_LENGTH];
    
    printf("Enter a string (consisting of 'a', 'b', and 'c'): ");
    fgets(tape, MAX_TAPE_LENGTH, stdin);
    tape[strcspn(tape, "\n")] = 0; // Remove newline character if present

    int tape_length = strlen(tape);
    if (tape_length == 0) {
        printf("Empty input is not accepted.\n");
        return 0;
    }

    // Run the Turing machine
    if (turing_machine(tape, tape_length)) {
        printf("\nThe string is accepted by the Turing machine.\n");
    } else {
        printf("\nThe string is not accepted by the Turing machine.\n");
    }

    return 0;
}

// Run the Turing machine
bool turing_machine(char tape[], int tape_length) {
    State state = q0;
    int head = 0;

    while (state != q5) {
        printf("\n Current Tape: %s and current state q%d with head value %d and read char %c", tape, state, head, tape[head]);
        switch (state) {
            case q0:
                if (tape[head] == 'a') {
                    tape[head] = 'X'; // Mark 'a'
                    head++;
                    state = q1; // Move to state q1
                } else if (tape[head] == 'Y') {
                    head++;
                    state = q4;
                } else {
                    return false; // Invalid input
                }
                break;
            case q1:
                if (tape[head] == 'a' || tape[head] == 'Y') {
                    head++;
                } else if (tape[head] == 'b') {
                    tape[head] = 'Y'; // Mark 'b'
                    head++;
                    state = q2; // Move to state q2
                } else {
                    return false; // Invalid input
                }
                break;

            case q2:
                if (tape[head] == 'b' || tape[head] == 'Z') {
                    head++;
                } else if (tape[head] == 'c') {
                    tape[head] = 'Z'; // Mark 'c'
                    head--;
                    state = q3; // Move to state q3
                } else {
                    return false; // Invalid input
                }
                break;

            case q3:
                if (tape[head] == 'Y' || tape[head] == 'Z' || tape[head] == 'a' || tape[head] == 'b') {
                    head--;
                } else if (tape[head] == 'X') {
                    head++;
                    state=q0;
                } else {
                    return false; // Invalid input
                }
                break;

            case q4:
                if (tape[head] == 'Y' || tape[head] == 'Z') {
                    head++;
                } else if (tape[head] == '\0') {
                    state = q5; // Move to state q0
                } else {
                    return false; // Invalid input
                }
                break;
        }
    }

    // Final check for acceptance
    for (int i = 0; i < tape_length; i++) {
        if (tape[i] == 'a' || tape[i] == 'b' || tape[i] == 'c') {
            return false; // Unmarked characters left
        }
    }

    return true;
}
