#include <stdio.h>
#include <ctype.h>
#define BUFSIZE 100
#define SIZE 1000

char buf[BUFSIZE]; //buffer for ungetch
int bufp = 0;      //next free position in buf

int getch(void);
void ungetch(int);
int getint(int *);

int main(void) {
	int n,s,array[SIZE],getint(int *);
	/*
	for(n = 0; n < SIZE && getint(&array[n]) != EOF; (res != 0)? n++ : 0) {
		printf("storing in n = %d, getint %d\n",n,array[n]);
	} */
	printf("storing in n = %d, getint %d\n",n,array[n]);
	
    for(s=0;s<=n; s++) {
        printf("%d",array[s]);
	}
}

int getch(void) { //get a possibly pushed backed character 
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) { // push character back on input 
	if(bufp >= BUFSIZE) {
		printf("ungetch: too many characters\n");
	} else {
		buf[bufp++] = c;
	}
}

int getint(int *pn) {
	int c,sign;
	
	while(isspace(c=getchar()))
		;
	
	if(!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c); //its not a number 
		return -1;
	}
	
	sign = (c == '-') ? -1 : 1;
	
	if(c == '+' || c == '-') {
		c = getch();
	}
	
	if(!isdigit(c)) {
		return 0;
	}
	
	for(*pn = 0; isdigit(c); c = getch()) {
		*pn = 10 * *pn + (c - '0');
	}
	
	*pn *= sign;
	
	if(c != EOF) {
		ungetch(c);
	}
	
	return c;
}
