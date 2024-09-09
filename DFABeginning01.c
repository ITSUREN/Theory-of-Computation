// TOC Lab 2: Implement a DFA for L = { set of all strings over {0,1} such that
// string start with 01
#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 20

enum states { q0, q1, qf, qd};
enum states delta(enum states, char);

int main() {
	char input[MAX];
	enum states current_state = q0;
	int i = 0;

	printf("Enter a binary string: ");
	fgets(input, MAX, stdin);
	input[strcspn(input, "\n")] = 0;
	char ch = input[i];
	while( ch !='\0') {
		// Validate if the character is a binary digit (0 or 1)
        if (ch != '0' && ch != '1') {
            printf("\nError: The string %s contains invalid character '%c'. Only 0 and 1 are allowed.\n", input, ch);
            return EXIT_FAILURE;  // Exit if the string contains invalid characters
        }

	    current_state = delta(current_state,ch);
		ch = input[++i];
  	}
  	
	if(current_state == qf)
	   printf("\n The string %s is accepted.\n",input);
	else 
	    printf("\n The string %s is not accepted.\n",input);	    

   return EXIT_SUCCESS;			
}


enum states delta(enum states state, char ch) {
       enum states current_state;
	   switch(state) {
			case q0:
				if(ch=='0')
				   current_state = q1;
				else
				   current_state = qd;
				break;
			case q1:
				if(ch=='1')
				   current_state = qf;
				else
				   current_state = qd;
				break;
			case qf:
				if(ch=='0' )
				   current_state = qf;
				else
				   current_state = qf;
				break;
			case qd:
				if(ch=='0')
				   current_state = qd;
				else
				   current_state = qd;
				break;
		}	
	return current_state;
}
