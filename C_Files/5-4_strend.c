#include <stdio.h>
#define MAXLINE 1000

int mgetline(char s[], int max);
int mystrlen(char *t);
int mstrend(char *, char *);

int main(void) {
	char s[MAXLINE], t[MAXLINE];
	int ret;
	mgetline(s,MAXLINE);
	mgetline(t,MAXLINE);
	ret = strend(s,t);
	printf("%d",ret);
}

int mgetline(char s[], int lim) {
	int c,i;
	
	for(i = 0; i < lim-1 && (c=getchar()) != EOF && c != '\n';++i) {
		s[i] = c;
	}
	if(c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}
int mstrend(char *s, char *t) {
	int len;
	len = mystrlen(t);
	
	while(*s != '\0') { // while(*s++)
		++s;
	}
	--s;
	while(*t != '\0') {
		++t;
	}
	--t;
	
}