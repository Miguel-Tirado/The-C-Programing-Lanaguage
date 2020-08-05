#include <stdio.h>
#include <string.h>

#define NUMERIC 1  //numeric sort 
#define DECR 2     //sorts in decreasing order 
#define LINES 100  //max num of lines to be sorted 

int numcmp(char *, char *);
int readlines(char *lineptr[], int maxlines);
void myqsort(void *v[], int left, int right, int (*comp) (void *, void *));
void writelines(char *lineptr[], int nlines, int decr);

static char option = 0;

int main(int argc, char *argv[]) {
    char *lineptr[LINES];
    int nlines;            // pointer to text lines
    int c, rc = 0;         // number of input lines read

    // (*++argv)[0] is getting the contents of the first character and comparing it to '-' 
    // ex) "apple"  (*++argv[0]) => 'a' 
    while(--argc > 0 && (*++argv)[0] == '-') {
        while (c = *++argv[0]) {
            // |= bitwise or operator 
            // option |= NUMERIC is the same as option = option | NUMERIC;
            switch (c) {
                case 'n': 
                    option |= NUMERIC;
                    break;
                case 'r':
                    option |= DECR;
                    break;
                default: 
                    printf("sort: illegal option %c\n",c);
                    argc = 1;
                    rc = -1;
                    break;
            }
        }
    }

    // placement is keyyyyyyyyyy
    // equivilant to if(argc != 0)
    if (argc) {
        printf("Usage: sort -nr \n");
    } else {
        if((nlines = readlines(lineptr, LINES)) > 0) {
            if(option & NUMERIC) {
                myqsort((void **)lineptr,0,nlines-1,(int (*)(void *,void *))numcmp);
            } else {
                myqsort((void **)lineptr,0,nlines-1,(int (*)(void *, void *))numcmp);
            }
            writelines(lineptr,nlines,option & DECR);
        } else {
            printf("input too big to sort \n");
            rc = -1;
        }
        return rc;
    }  
}

//write output lines 
void writelines(char *lineptr[], int nlines, int decr) {
    int i;

    if(decr) {   // decr != 0
        for(i = nlines - 1; i >= 0; i--) {
            printf("%s\n",lineptr[i]);
        }
    } else {
        for(i = 0;i < nlines; i++) {
            printf("%s\n", lineptr[i]);
        }
    }
}

#include <stdlib.h>
//compare s1 and s2 numerically 
int numcmp(char *s1, char *s2) {
    double v1,v2;

    //atof() converts the string value into a double value 
    // note string is just an aray of characters 
    v1 = atof(s1);
    v2 = atof(s2);

    if (v1 < v2) {
        return -1;
    } else if(v1 > v2) {
        return 1;
    } else {
        return 0;
    }
}         

#define MAXLEN 1000  // MAX length of any input line
int mgetline(char *,int);
char *alloc(int);        //function returning a pointer to char 

int readlines(char *lineptr[], int maxlines) {
    int len, nlines;    //length, number of lines
    char *p,line[MAXLEN];
    nlines = 0;
    while((len = mgetline(line,MAXLEN)) > 0) {
        if(nlines >= maxlines || (p = alloc(len)) == NULL) {
            return -1;
        } else {
            line[len-1] = '\0';  //deletes newline
            strcpy(p,line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}

#define ALLOCSIZE 1000  //size of avalable space
static char allocbuf[ALLOCSIZE]; //storage for alloc
static char *allocp = allocbuf;  //next free positon 

char *alloc(int n) {   // return pointer to n characters 
    if(allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return allocp - n;
    } else {
        return 0;
    }
}

//free storage pointed to by p
void afree(char *p) {
    if(p >= allocbuf && p < allocbuf + ALLOCSIZE) {
        allocp = p;
    }
}

//my qsort v[left] ... c[right] into increasing order 
void myqsort(void *v[],int left,int right,int (*comp)(void *, void *)) {
    int i, last;
    void swap(void *v[], int, int);

    if(left >= right) {
        return;
    }

    swap(v,left,(left + right)/2);

    last = left;

    for(i = left + 1; i <= right;i++) {
        if((*comp)(v[i], v[left]) < 0) {
            swap(v,++last,i);
        }
    }
    swap(v,left,last);

    myqsort(v,left,last-1,comp);
    myqsort(v,last+1,right,comp);
}

void swap(void *v[],int i, int j) {
    void *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

//mgetline: read a line into s, return length
int mgetline(char s[], int lim) {
    int c,i;

    for(i=0;i<lim-1 && (c=getchar()) != EOF && c!='\n';++i) {
        s[i] = c;
    }
    if(c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i; 
}