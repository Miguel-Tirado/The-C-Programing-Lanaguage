//1.9 character array example miguel Tirado
#include <stdio.h>
#define MAXLINE 1000               /* maximum input line size */

int getline(char line[], int maxline);
void copy(char to[], char from[]);

// print logest input
int main(void) {
	int len;                   // current line length 
	int max;                   // maximum length seen so far 
	char line[MAXLINE];        // current input line 
	char longest[MAXLINE];     // logest line saved here
	
	max = 0;
	while((len = getline(line, MAXLINE)) > 0) {
		if(len > max) {
			max = len;
			copy(longest, line);
		}
	}
	// there was a line, below 
	if (max > 0) {
		printf("%s",longest);
	}
}

// getline: read a line into s, return length 
int getline(char s[], int lim) {
	int c, i;
	for(i = 0; i < lim-1 && (c = getchar()) != EOF && c !='\n'; ++i) {
		s[i] = c;
	}
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	// The \0 indicated the the end of the char array 
	// example: h e l l o \n \0 
	s[i] = '\0';
	return i;
}

// copy: copy 'from' into 'to'; assume  to is beg enouph 
void copy(char to[], char from[]) {
	int i;
	
	i = 0;
	while ((to[i] = from[i]) != '\0') {
		++i;
	}
}