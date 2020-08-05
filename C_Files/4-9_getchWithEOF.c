/* getch and ungetch to handle EOF character In all the ungetch and getch
   functions written so far, the buf is declared as char buf[BUDSIZ]. 
   Changing this to int buf[BUFSIZ} enable it to handle EOF. As EOF is an
   Intger declared in stdiho.h having the value -1*/

#include<stdio.h>
#define BUFSIZE 100

int getch(void);
void ungetch(int c);

int buf[BUFSIZE];
int bufp = 0;

int main(void) {
	int c;
	
	c = '*';
	
	ungetch(c);
	while((c = getch()) != EOF) {
		putchar(c);
	}
}

int getch(void) {
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
	if (bufp >= BUFSIZE) {
		printf("ungetch: too many characters");
	} else {
		buf[bufp++] = c;
	}
}