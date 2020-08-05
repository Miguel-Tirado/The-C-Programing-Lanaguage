//Miguel Tirado Word Counting Program EX 1.5.4 in book 
#include <stdio.h>

//Defining my constants or macros 
#define IN 1  /* insdie a word */
#define OUT 0 /* outside a word */
//bug it wont record my values for nl,nw, or nc if i havnt entered them in yet 
int main() {
	int c,nl,nw,nc, state;
	//nc = new characters, nl = new line, nw = new word 
	nl = nw = nc =0;
	while((c = getchar()) != EOF) {
		++nc;
		if(c == '\n') {
			++nl;
		}
		if (c == ' ' || c == '\t' || c == '\n') {
			state = OUT;
		} else if (state == OUT) {
			nw++;
		}
	}
	printf("\nNew Characters: %d, New Line: %d, New Word: %d", nc,nl,nw);
	return 0;
}