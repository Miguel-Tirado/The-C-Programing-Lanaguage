/* write a program that replaces tabs in the input with proper number of blanks to space to the next tab stop.
Assume a fixed set of tab stops, say every n columns.should n be a barable or symbolic parameter?   */
//Miguel Tirado

#include <stdio.h>

#define TABINC 8
// 8 since 8 spaces make up 1 tab

int main(void) {
	int nb,pos,c;
	
	nb = 0;
	pos = 1;
	
	while((c = getchar()) != EOF) {
		if (c == '\t') {
			nb = TABINC - ((pos-1)%TABINC);
			while(nb >0) {
			putchar('#');
			++pos;
			--nb;
			}
		}
		else if(c == '\n') {
		putchar(c);
		pos = 1;
		} 
		else {
			putchar(c);
			++pos;
		}
	}	
}