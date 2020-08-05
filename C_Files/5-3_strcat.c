#include <stdio.h>

void mstrcat(char *, char *);

int main(void) {
	
	char hello[11];
	char bye[4];
	
	hello[0] = 'h';
	hello[1] = 'e';
	hello[2] = 'l';
	hello[3] = 'l';
	hello[4] = 'o';
	hello[5] = '\0';

	bye[0] = 'b';
	bye[1] = 'y';
	bye[2] = 'e';
	bye[3] = '\0';
	
	mstrcat(hello,bye);
	
	printf("%s\n",hello );
	
}

void mstrcat(char *s, char *t) {
	while(*s++ != '\0')
		;
	*s--; // removes the first termination character from the first string \0 from "hello\0"
	while(*s++ = *t++) 
		;
	/*  the above while loop is the same as the following loop 
	while ((s*=t*)!='\0') {
		s++;
		t++;
	}		*/
	
	
}

