#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define NUMBER '0' // signal that the number was found 
#define MAXVAL 100 // maximum depth of val stack
#define BUFSIZE 100
#define MAXLINE 1000
#define MAXOP 100

int getch(void);
void ungetch(int);
int getop(char *);
void push(double);
double pop(void);

int mgetline(char *line, int max);
int strindex(char *x, char *t);
int atoiv2(char *);
void itoav2(int n, char *s);
void reverse(char *);

int sp = 0;
int bufp = 0;
double val[MAXVAL];
char buf[BUFSIZE];

char pattern[] = "ould";

int main(void) {
	char line[MAXLINE];
	int found = 0;
	
	while((mgetline(line,MAXLINE)) > 0) {
		if(strindex(line,pattern) > 0) {
			printf("%s\n",line);
			found++;
		}
	}
	
	char *s = "1234";
	int ret;
	
	ret = atoiv2(s);
	printf("%d\n",ret);
	char s1[100];
	int i = 12345;
	itoav2(i,s1);
	
	reverse(s1);
	printf("%d\n",ret);
	
	int type;
	double op2;
	char s3[MAXOP];
	
	while((type = getop(s3)) != EOF) {
		switch(type) {
			case NUMBER:
				push(atof(s3));
				break;
			case '+': 
				push(pop() + pop());
				break;
			case '*':
				push(pop() * pop());
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case '/':
				op2 = pop();
				if(op2 != 0.0) {
					push(pop() / op2);
				} else {
					printf("error: cant divide by zero\n");
				}
				break;
			case '\n': 
				printf("\t%.8g\n",pop());
				break;
			default:
				printf("error: unkown command %s\n",s);
				break;
		}
	}
	
}

int atoiv2(char *s) {
	int n, sign;
	
	for(;isspace(*s);s++) //removes spaces 
		;
	
	sign = ( *s == '-') ? -1:1;
	
	if(*s == '+' || *s == '-') {
		s++;
	}
	for(n =0; isdigit(*s);s++) {
		n = 10 *n + *s - '0';
	}
	
	return sign * n;	
}

//push: push f onto value stack
void push(double f) {
	if(sp < MAXVAL) {
		val[sp++] = f;
	} else {
		printf("error: stack full, can't push %g\n",f);
	}
}

double pop(void) {
	if(sp > 0) {
		return val[--sp];
	} else {
		printf("error: stack empty\n");
		return 0.0;
	}
}

/* getop: get next operator or numeric operand  pointer version */

/* getop */
int getop(char *s)
{
    int c;
    
    while((*s=c=getch()) == ' ' || c == '\t')
        ;
    *(s+1) = '\0';

    if(!isdigit(c) && c!='.')
        return c;       /* not a number */
    if(isdigit(c))
    while(isdigit(*++s = c = getch()))
        ;

    if(c == '.')
    while(isdigit(*++s = c = getch()))
        ;

    *s = '\0';

    if(c != EOF)
        ungetch(c);
    return NUMBER;
}

int getch(void)
{
    return (bufp > 0) ? buf[--bufp]:getchar();
}

void ungetch(int c)
{
    if(bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++]=c;
}

/* itoa */

void itoav2(int n,char *s)
{
    int sign;
    char *t=s;
    
    if((sign = n) < 0)
        n = -n;

    do
    {
        *s++ = n % 10 + '0';
    } while ((n /= 10) > 0);

    if(sign < 0)
        *s++ = '-';
    *s='\0';

}

/* reverse */

void reverse(char *s)
{
    int c;
    char *t;

    for(t=s+(strlen(s)-1);s<t;s++,t--)
    {
        c=*s;
        *s=*t;
        *t=c;
    }
}
/* mgetline */

int mgetline(char *s,int lim)
{
    int c;
    char *t=s;

    while(--lim > 0 && (c=getchar())!='X' && c!='\n')
        *s++=c;

    if(c=='\n')
        *s++=c;
    *s='\0';

    return s-t;
}

/* strindex */

int strindex(char *s,char *t)
{
    char *b=s;
    char *p,*r;

    for(;*s!='\0';s++)
    {
        for(p=s,r=t;*r!='\0' && *p==*r;p++,r++)
            ;

            if(r>t && *r == '\0')
                return s-b;
    }
    return -1;
}

