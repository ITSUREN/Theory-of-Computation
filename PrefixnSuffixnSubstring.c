#include<stdio.h>
#include<string.h>
#define MAX_INPUT_LENGTH 20

// function prototyping
void find_prefix(char string[]);
void find_suffix(char string[]);
void find_substring(char string[], int, int);

int main() {
    char string[MAX_INPUT_LENGTH];
    int i, j;

    printf("Enter a string: ");
    // Use fgets instead of gets
    fgets(string, MAX_INPUT_LENGTH, stdin);
    string[strcspn(string, "\n")] = '\0';  // Removes the trailing newline from fgets

    printf("\n Prefixes:");
    find_prefix(string);

    printf("\n Suffixes:");
    find_suffix(string);

    do {
        printf("\nEnter i (start index) and j (end index) for substring [1-N]: ");
        scanf("%d%d", &i, &j);
    } while (i < 1 || j > strlen(string) || i > j);  // Ensure valid indices

    find_substring(string, i, j);
    return 0;
}

void find_prefix(char string[]) {
    int i, j;
    char prefix[20];
    for (i = strlen(string); i >= 0; i--) {
        for (j = 0; j < i; j++) {
            prefix[j] = string[j];
        }
        prefix[j] = '\0';
        printf("\n %s", prefix);
    }
}

void find_suffix(char string[]) {
    int i, j, k;
    char suffix[20];
    for (i = 0; i <= strlen(string); i++) {
        k = i;
        for (j = 0; j < strlen(string); j++) {
            suffix[j] = string[k];
            k++;
        }
        suffix[j] = '\0';
        printf("\n %s", suffix);
    }
}

void find_substring(char string[], int x, int y) {
    char substr[20];
    int k = 0, i;
    
    // Adjust the 1-based indices to 0-based
    for (i = x - 1; i < y; i++) {
        substr[k] = string[i];
        k++;
    }
    substr[k] = '\0';
    printf("\n Substring: %s\n", substr);
}
