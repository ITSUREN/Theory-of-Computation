#include<stdio.h>
#include<string.h>

#define MAX_INPUT_LENGTH 20

// State Definition, Keyword Dictionary and function prototyping
char keyword[32][10] = {
    "auto", "double", "int", "struct", "break", "else", "long", "switch", "case",
    "enum", "register", "typedef", "char", "extern", "return", "union", "const",
    "float", "short", "unsigned", "continue", "for", "signed", "void", "default",
    "goto", "sizeof", "volatile", "do", "if", "static", "while"
};
enum states { q0, qf, qd };
enum states delta(enum states, char);
int isKeyword(char[]);

int main() {
    enum states curr_state = q0;
    char string[MAX_INPUT_LENGTH], ch;
    int i = 0;

    printf("\nEnter a string: ");
    fgets(string, MAX_INPUT_LENGTH, stdin);
    string[strcspn(string, "\n")] = 0;

    ch = string[i];

    if (isKeyword(string)) {
        printf("\nThe string %s is a keyword.\n", string);
    } else {
        while (ch != '\0') {
            curr_state = delta(curr_state, ch);
            ch = string[++i];
        }

        if (curr_state == qf) {
            printf("\nThe string %s is a valid identifier.\n", string);
        } else {
            printf("\nThe string %s is neither a keyword nor a valid identifier.\n", string);
        }
    }
    return 0;
}

enum states delta(enum states s, char ch) {
    enum states curr_state;

    switch (s) {
        case q0:
            if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || ch == '_')
                curr_state = qf;
            else
                curr_state = qd;
            break;

        case qf:
            if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || ch == '_' || (ch >= '0' && ch <= '9'))
                curr_state = qf;
            else
                curr_state = qd;
            break;

        case qd:
            curr_state = qd;
            break;
    }

    return curr_state;
}

int isKeyword(char str[]) {
    for (int i = 0; i < 32; i++) {
        if (strcmp(str, keyword[i]) == 0)
            return 1;
    }
    return 0;
}
