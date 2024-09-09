#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 100

// Function prototypes
bool parse_S(const char *input, int start, int end);

// Check if a substring from `start` to `end` matches the CFG rule
bool parse_S(const char *input, int start, int end) {
    if (start > end) {
        return false;
    }

    // Base cases for single characters
    if (start == end) {
        return input[start] == 'a' || input[start] == 'b';
    }

    // Try matching the rule S -> aSa
    if (input[start] == 'a' && input[end] == 'a') {
        return parse_S(input, start + 1, end - 1);
    }

    // Try matching the rule S -> bSb
    if (input[start] == 'b' && input[end] == 'b') {
        return parse_S(input, start + 1, end - 1);
    }

    return false;
}

int main() {
    char input[MAX];
    int length;

    printf("Enter a string (consisting of only 'a' and 'b'): ");
    fgets(input, MAX, stdin);
    input[strcspn(input, "\n")] = 0; // Remove newline character if present

    length = strlen(input);
    
    if (parse_S(input, 0, length - 1)) {
        printf("The string \"%s\" is accepted by the CFG.\n", input);
    } else {
        printf("The string \"%s\" is not accepted by the CFG.\n", input);
    }

    return 0;
}
