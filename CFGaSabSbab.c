#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_INPUT_LENGTH 100

// brute parser prototyping
bool parse(const char *input, int start, int end);

int main() {
    char input[MAX_INPUT_LENGTH];
    int length;

    printf("\nEnter the string: ");
    fgets(input, MAX_INPUT_LENGTH, stdin);
    input[strcspn(input, "\n")] = 0; // Remove newline character if present

    length = strlen(input);
    
    if (parse(input, 0, length - 1)) {
        printf("The string %s is accepted by the CFG.\n", input);
    } else {
        printf("The string %s is not accepted by the CFG.\n", input);
    }

    return 0;
}

// Check if a substring from `start` to `end` matches the CFG rule
bool parse(const char *input, int start, int end) {
    if (start > end) {
        return false;
    }

    // Base cases for single characters: S->a | S-> b
    if (start == end) {
        return input[start] == 'a' || input[start] == 'b';
    }

    // Try matching the rule S -> aSa
    if (input[start] == 'a' && input[end] == 'a') {
        return parse(input, start + 1, end - 1);
    }

    // Try matching the rule S -> bSb
    if (input[start] == 'b' && input[end] == 'b') {
        return parse(input, start + 1, end - 1);
    }

    return false;
}