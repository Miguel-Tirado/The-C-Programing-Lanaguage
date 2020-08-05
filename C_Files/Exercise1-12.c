//Miguel Tirado 
#include <stdio.h> 

#define IN 1  /* insdie a word */
#define OUT 0 /* outside a word */

int main (void) {
	int c,nl,nw,nc, state;
	//nc = new characters, nl = new line, nw = new word 
	state = IN;
	while((c = getchar()) != EOF) {
		if (c == ' ' || c == '\t' ) {
			state = OUT;
		} else if (state == OUT) {
			state = IN;
			putchar('\n');
			putchar(c);
		} else { 
			putchar(c);
		}
	}
	//printf("\nNew Characters: %d, New Line: %d, New Word: %d", nc,nl,nw);
}