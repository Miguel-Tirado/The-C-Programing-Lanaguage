/* Program to print all inputs that are longer than 80 characters.*/
// Exercise 1-17 Miguel Tirado 
#include <stdio.h>

#define MAXLINE 1000
#define LIMIT 80

int ngetline(char line[], int lim);

int main (void) {
	int len;
	char line[MAXLINE];
	
	while ((len = ngetline(line,MAXLINE))  > 0) {
		if(len > LIMIT) {
			printf("%s",line);
		}
	}
}

int ngetline(char s[], int lim) {
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