#include <stdio.h>
#include <math.h>

#define MAXOP 100       //max size of operand or operator
#define NUMBER '0'      //signal that a number was found 

int getop(char []);
void ungets(char []);
void push(double);
double pop(void);

int main(int argc, char *argv[]) {
    char s[MAXOP];
    double op2;

    while(--argc > 0) {
        ungets(" ");
        ungets(*++argv);
        switch(getop(s)) {
            case NUMBER: 
                push(atof(s));
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
                if(op2 != 0) {
                    push(pop() / op2);
                } else {
                    printf("Error: divide by zero\n");
                }
                break;
            default: 
                printf("Error: unkown command %s \n",s);
                argc = 1;
                break;
        }
    }
    printf("\t %8g\n",pop());

    return 0;
    
}

#include <ctype.h>

int getch(void);
void ungetch(int);

//gettop: get next operator or numeric operand

int getop(char s[]) {
    int i,c;

    while((s[0] = c = getch()) == ' ' || c == '\t') 
        ;
    s[1] = '\0';

    if(!isdigit(s[++i] = c = getch())) {
        while(isdigit(s[++i] = c = getch()))
            ;
        
    }
    if( c == '.') /* collect from fraction part */
        while(isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    
    if(c != EOF)
        ungetch(c);
    return NUMBER;
}

#define BUFSIZE 100
char buf[BUFSIZE];  /* buffer for ungetch */
int bufp = 0;       /* next free position in buf */

int getch(void) /* get a (possibly pushed back) character */
{
    return (bufp > 0)? buf[--bufp]: getchar();
}

void ungetch(int c) /* push character back on input */
{
    if ( bufp >= BUFSIZE)
        printf("ungetch: too many characters \n");
    else
        buf[bufp++] = c;
}

#define MAXVAL 100 /* maximum depth of value of stack */

int sp = 0; /* next free stack position */
double val[MAXVAL];     /* value stack */

/* push : push f onto value stack */
void push(double f)
{
    if(sp < MAXVAL)
        val[sp++] =f;
    else
        printf("error: stack full, can't push %g \n",f);
}

/* pop: pop and return top value from the stack */

double pop(void)
{
    if ( sp > 0)
        return val[--sp];
    else
    {
        printf("error: stack empty \n");
        return 0.0;
    }
}

#include<string.h>
/* ungets: push string back onto the input */

void ungets(char s[])
{
    int len=strlen(s);
    void ungetch(int);

    while(len > 0)
        ungetch(s[--len]);
}
