// TOC Lab : Implement a PDA for L = { set of all strings over {0,1} such that
// equal number of 0s and 1s , acceptance by final state
#include<stdio.h>
#include<string.h>
#define MAX_INPUT_LENGTH 20

// State Definitions and function prototyping
enum states { q0, q1,qf };
void push(char ch);
void pop();
char get_stack_top();
enum states delta(enum states, char, char);

struct stack {
	char symbols[MAX_INPUT_LENGTH];
	int top;
} st;

int main() {
	char input[MAX_INPUT_LENGTH];
	enum states curr_state = q0;
	st.top = -1;
	int i =0, c=0;
	char ch = 'e', st_top = 'e';
	curr_state = delta(curr_state,ch,st_top);
	
	printf("\n Enter a binary string: ");
	fgets(input, MAX_INPUT_LENGTH, stdin);
	input[strcspn(input, "\n")] = 0;

	ch = input[i];
	st_top = get_stack_top();
	while ( c <= strlen(input)) {
		ch = input[i];
		curr_state = delta(curr_state,ch,st_top);
		st_top=get_stack_top();
		c++; i++;
    }

	if (curr_state == qf)
	   printf("\n The string %s is accepted.\n",input);
	else 
	    printf("\n The string %s is not accepted.\n",input);	    	
   return 0;			
}

enum states delta(enum states s, char ch, char st_top) {
	enum states curr_state;
	switch(s) {
		case q0:
			if (ch=='e' && st_top=='e') {
				curr_state = q1;
				push('$');
			}
			break;
		case q1:
			if (ch=='0' && (st_top=='$' || st_top=='0')) {
				curr_state = q1;
				push(ch);
			} else if (ch=='1' && (st_top=='$'||st_top=='1')) {
				curr_state = q1;
				push(ch);
			} else if ((ch=='1' && st_top=='0')||(ch=='0'&&st_top=='1')) {
				curr_state = q1;
				pop();
			} else if (ch=='\0' && st_top=='$') {
				curr_state = qf;
			}
			break;
	}
	return curr_state;
}


char get_stack_top() {
	return (st.symbols[st.top]);
}

void push(char ch) {
	if (st.top<MAX_INPUT_LENGTH-1 )
	  	st.symbols[++st.top] = ch;
	else
		printf("\n Stack Full.");
}

void pop() {
	if (st.top>-1){
		st.symbols[st.top]=' ';
		st.top--;
	} else
		printf("\n Stack Empty.");
}
