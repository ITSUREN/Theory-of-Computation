// Implement DFA that accepts strings with sub string 001 over {0,1}
#include<stdio.h>
#include <string.h>
#define MAX_INPUT_LENGTH 20

// State Definitions
enum states { q0, q1, q2, qf };
enum states delta(enum states, char);

int main() {
	enum states curr_state = q0;
	char string[MAX_INPUT_LENGTH], ch;
	int i=0;
	
	printf("Enter a string: ");
	fgets(string, MAX_INPUT_LENGTH, stdin);
	string[strcspn(string,"\n")] = 0;
	
	ch = string[i];
	while(ch!='\0') {
		curr_state = delta(curr_state,ch);
		ch = string[++i];
	}

	if(curr_state==qf)
	  printf("\n The string %s is valid.\n",string);
	else 
	  printf("\n The string %s is not valid.\n",string);
	  
	return 0;
}

enum states delta(enum states s, char ch) {
	enum states curr_state;
	switch(s) {
		case q0:
			if(ch=='0')
			   curr_state = q1;
			else
			   curr_state = q0;
			break;
		case q1:
			if(ch=='0')
			   curr_state = q2;
			else
			   curr_state = q0;
			break;
		case q2:
			if(ch=='0')
			   curr_state = q2;
			else
			   curr_state = qf;
			break;
		case qf:
			if(ch=='0'||ch=='1')
			   curr_state = qf;
	}
	return curr_state;
} 
