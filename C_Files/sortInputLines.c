/* program that will sort a set of text lines into alphabetic order 
   similer to unix sort */
#include <stdio.h>
#include <string.h>

#define MAXLINES 5000  // max number of lines to be sorted 

char *lineptr[MAXLINES]; //pointers to texlines 

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

// sort input lines 
int main() {
	int nlines;      // number of input lines read 
	
	if((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		qsort(lineptr, 0, nlines-1);
		writelines(lineptr, nlines );
		return 0;
	} else {
		printf("error: input too big to sort\n");
		return 1;
	}
}

#define MAXLEN 1000    // max length of any input lines
int getline(char *, int); // need to make this function!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
char *alloc(int);

//readlines: read input-lines 
int readlines(char *lineptr[], int maxlines) {
	int len, nlines;
	char *p, line[MAXLEN];
	
	nlines = 0;
	while((len = getline(line,MAXLEN)) > 0) {
		if(nlines >= MAXLINES || (p = alloc(len)) == NULL) {
			return -1;
		} else {
			line[len-1] = '\0'; // deletes newline
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	}
	return nlines;
}

//writelines: write output lines 
void writelines(char *lineptr[], int nlines) {
	int i;
	
	for(i = 0; i < nlines;i++) {
		printf("%s\n",lineptr[i]);
	}
}

// qsort: sort v[left]...v[right] into increasing order 
void qsort(char *v[], int left, int right) {
	int i, last;
	void swap(char *v[],int i, int j);
	
	if(left >= right) {   // do nothing if array contains fewer than 2 elements 
		return;
	}
	swap(v,left, (left + right)/2);
	last = left;
	for(i = left+1; i <= right;i++) {
		if(strcmp(v[i], v[left]) < 0){
			swap(v,++last,i);
		}
		swap(v,left,last);
		qsort(v,left,last-1);
		qsort(v, last+1,right);
		
	}
}

void swap(char *v[],int i,int j) {
	char *temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}