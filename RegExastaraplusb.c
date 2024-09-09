#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX 20

// Define states
typedef enum { q0, q1, qf } state;

// Transition function for NDFA
state delta(state current_state, char ch);

// Check if the string matches the regular expression
bool matches_regex(const char *string);

int main() {
    char string[MAX];
    
    printf("Enter a string: ");
    fgets(string, MAX, stdin);
    string[strcspn(string, "\n")] = 0; // Remove newline character
    
    if (matches_regex(string)) {
        printf("\nThe string \"%s\" matches the regular expression a*(a+b).\n", string);
    } else {
        printf("\nThe string \"%s\" does not match the regular expression a*(a+b).\n", string);
    }
    
    return 0;
}

// Transition function for NDFA
state delta(state current_state, char ch) {
    switch (current_state) {
        case q0:
            if (ch == 'a') return q0; // Stay in q0 on 'a'
            if (ch == 'a' || ch == 'b') return q1; // Transition to q1 on 'a' or 'b'
            break;
        case q1:
            if (ch == 'a' || ch == 'b') return qf; // Transition to qf on 'a' or 'b'
            break;
        case qf:
            return qf;
    }
    return qf; // Default transition to qf if input is invalid
}

// Check if the string matches the regular expression
bool matches_regex(const char *string) {
    state current_state = q0;
    
    for (int i = 0; string[i] != '\0'; ++i) {
        char ch = string[i];
        current_state = delta(current_state, ch);
    }
    
    // Accept if we end in state q1 (indicating the string ends with one 'a' or 'b')
    return current_state == q1;
}
