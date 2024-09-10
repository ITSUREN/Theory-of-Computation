#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_TAPE_LENGTH 100

// State Definitions and Turing Function prototyping
typedef enum { q0, q1, q2, q3, q4, q5 } State;
bool turing_machine(char tape[], int tape_length);

int main() {
    char tape[MAX_TAPE_LENGTH];
    
    printf("Enter a string: ");
    fgets(tape, MAX_TAPE_LENGTH, stdin);
    tape[strcspn(tape, "\n")] = 0; // Remove newline character if present

    int tape_length = strlen(tape);
    if (tape_length == 0) {
        printf("Empty input is not accepted.\n");
        return 0;
    }

    // Runing the Turing machine
    if (turing_machine(tape, tape_length)) {
        printf("\nThe string is accepted by the Turing machine.\n");
    } else {
        printf("\nThe string is not accepted by the Turing machine.\n");
    }
    return 0;
}

bool turing_machine(char tape[], int tape_length) {
    State state = q0;
    int head = 0;

    while (state != q5) {
        switch (state) {
            case q0:
                if (tape[head] == 'a') {
                    tape[head] = 'X'; // Mark 'a'
                    head++;
                    state = q1; 
                } else if (tape[head] == 'Y') {
                    head++;
                    state = q4;
                } else {
                    return false; 
                }
                break;
            case q1:
                if (tape[head] == 'a' || tape[head] == 'Y') {
                    head++;
                } else if (tape[head] == 'b') {
                    tape[head] = 'Y'; // Mark 'b'
                    head++;
                    state = q2;
                } else {
                    return false; 
                }
                break;

            case q2:
                if (tape[head] == 'b' || tape[head] == 'Z') {
                    head++;
                } else if (tape[head] == 'c') {
                    tape[head] = 'Z'; // Mark 'c'
                    head--;
                    state = q3;
                } else {
                    return false; 
                }
                break;

            case q3:
                if (tape[head] == 'Y' || tape[head] == 'Z' || tape[head] == 'a' || tape[head] == 'b') {
                    head--;
                } else if (tape[head] == 'X') {
                    head++;
                    state=q0;
                } else {
                    return false; 
                }
                break;

            case q4:
                if (tape[head] == 'Y' || tape[head] == 'Z') {
                    head++;
                } else if (tape[head] == '\0') {
                    state = q5; 
                } else {
                    return false; 
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
