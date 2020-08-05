/*Exercise 3-3 function expand(s1,s2) that expands short hand notations like a-z
 *in the string s1 into the equivilant complete list abc...xyz in s2. */

#include <stdio.h>
#define MAXLINE 1000

int mgetline(char s[], int maxlimit);
void expand(char a[], char b[]);

int main(void) {
	char s1[MAXLINE], s2[MAXLINE];
	mgetline(s1, MAXLINE);
	expand(s1, s2);
	
	printf("%s", s2);
	
}

int mgetline(char s[], int lim) {
	int c,i;
	
	for(i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i) {
		s[i] = c;
	}
	
	if(c == '\n') {
		s[i++] = c;
	}
	s[i] = '\0';
}

void expand(char s1[], char s2[]) {
	int i,j,c;
	
	i = j = 0;
	while((c = s1[i++]) != '\0') {
		if(s1[i] == '-' && s1[i+1] >= c) {
			i++;
			while(c < s1[i]) {
				s2[j++] = c++;
			} 
		} else {
			s2[j++] = c;
		}
	}
}
/* Here we expand the strings like a-z from s1 into an expanded form in s2. We utilize the ascii table property that the second character is higher than the first character and it is incremental.

In the outer while loop, we get the character in c, and then check if the next character is - and character beyond that (i+1) is greater than c. With this check, we ascertain that we are in a range like a-z.

To expand the range, we keep incrementing the character in c, till it hits the end character, storing all the characters in s2.

s2 will now have the expanded string */