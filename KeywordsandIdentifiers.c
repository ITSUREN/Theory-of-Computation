// to identify valid identifiers and keywords in C
#include<stdio.h>
#include<string.h>
#define MAX 20

char keyword[32][10]={"auto","double","int","struct","break","else","long",
       "switch","case","enum","register","typedef","char",
       "extern","return","union","const","float","short",
       "unsigned","continue","for","signed","void","default",
       "goto","sizeof","voltile","do","if","static","while"} ;
enum states { q0, qf };
enum states delta(enum states, char);
int iskeyword(char []);

int main()
{
	enum states curr_state = q0;
	char string[MAX], ch;
	int i=0;
	
	printf("\n Enter a string: ");
	fgets(string, MAX , stdin);
	string[strcspn(string, "\n")]=0;
	
	ch = string[i];
	if(iskeyword(string))
	   printf("\n The string %s is keyword.\n",string);
	else {
		while(ch!='\0') {
			curr_state = delta(curr_state,ch);
			ch = string[++i];
		}
		if(curr_state==qf)
	 		 printf("\n The string %s is valid indentifier.\n",string);
		else 
	 		 printf("\n The string %s is neither keyword nor valid identifier.\n",string);	
	}	 
	return 0;
} 

enum states delta(enum states s, char ch) {
	enum states curr_state;
	switch(s) {
		case q0:
			if(ch>='A' && ch<='Z'||ch>='a'&&ch<='z'||ch=='_')
			   curr_state = qf;
			break;
		case qf:
			if(ch>='A' && ch<='Z'||ch>='a'&&ch<='z'||ch=='_'||ch>='0'&&ch<='9')
			   curr_state = qf;	
			break;
	}
	return curr_state;
}


int iskeyword(char str[]) {
	for(int i=0;i<32;i++){
		if(strcmp(str,keyword[i])==0)
		   return 1;
	}
	return 0;
	
} 
