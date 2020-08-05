#include <stdio.h>

#define MAXLINE 1000

int mgetline(char line[], int lim);
int removetrail(char rline[]);

int main(void) {
	int len;
	char line[MAXLINE];
	
	while((len = mgetline(line, MAXLINE))>0) {
		if(removetrail(line) > 0) {
			printf("%s",line);
		}
	}
}
int mgetline(char s[], int lim) {
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

int removetrail(char s[]) {
	int i;
	
	// To consider raw line without \n 
	for (i =0; s[i] != '\n';++i) 
		;
	--i;
	
	// removing the traling Blancks and tab spaces
	for(i = 0;((s[i] == ' ')||(s[i] == '\t'));--i)
		;
	
	if (i >= 0) { // non empty line 
		++i;
		s[i] = '\n';
		++i;
		s[i] = '\0';
	}
	
	return i;
	
}