/* Exercise 4.1 write the function strindex(s,t) which returns the position of the rightmost occurance of t in s, or -1 if there is none. */
#include <stdio.h>

int mstrindex (char source[], char strPattern[]);

int main(void) {
	char line[] = "abcdedfabcde";
	char pattern[] = "abc";
	
	int found;
	
	/* it should match the a the 7th position */
	
	found = mstrindex(line,pattern);
	printf("Found the right index: %d\n", found);
}

int mstrindex(char s[], char p[]) {
	int i,j,k,result;
	
	result = -1;
	
	for(i = 0; s[i] != '\0'; i++) {
		for(j = i, k = 0; p[k] != '\0' && s[j] == p[k]; j++,k++) 
			;
		if(k > 0 && p[k] == '\0') {
			result = i;
		}
	}
	return result;
}

/* The outer loop goes over each character in string s and in the inner we check if we find a substring t maching
   in the outer loop. If we find the substring match, we dont break the loop, but record the position i and proceed
   further. Thus our right most match is noted. If no search is found, then the result, -1 is returned    */