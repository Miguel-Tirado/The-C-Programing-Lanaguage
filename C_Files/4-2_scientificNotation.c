/* program demonstrating atof(char s[]). the function which converts the sting to floating point view */
#include <stdio.h>
#include <ctype.h>
#define MAXLINE 100

double myatof(char s[]);
int mgetline(char line[], int maxline);
// there is typo sum where here that making it return just zero some where.

int main (void) {
	char str[MAXLINE];
	double num;
	mgetline(str,MAXLINE);
	
	num = myatof(str);
	printf("%f", num);
}

double myatof (char s[]) {
	double val,pow;
	int sign,i,esign,exp;
	int power(int base, int exp);
	//the declaration above is stating that power is a function that takes int base and int exp and returns a int 
	
	for(i = 0; isspace(s[i]); i++) // this skips white spaces 
		;
	
	sign =(s[i] == '-') ? -1 : 1;
	
	if(s[i] == '+' || s[i] == '-') {
		i++;
	}
	
	for(val = 0.0; isdigit(s[i]); i++) { // this is used to convert numeric characters into there double value 
		val = 10.0 * val + (s[i] - '0');
	}
	
	if(s[i] == '.') {  // used this to skip the . used in scientific notation i.e) 1.0e3
		i++;
	}
	
	for(pow = 1.0; isdigit(s[i]); i++) { //used to get the calculate the power value 
		val = 10.0 * val + (s[i] - '0');
		pow *= 10.0;
	}
	
	if(s[i] == 'e' || s[i] == 'E') {
		i++;
	}
	
	if(s[i] == '+' || s[i] == '-') {
		esign = s[i];
		i++;
	}
	
	for(exp = 0; isdigit(s[i]); i++) {
		exp = 10.0 * exp + (s[i] = '0');
	}
	
	if(esign == '-') {
		return sign * (val/pow) / power(10,exp);
	} else {
		return sign * (val/pow) * power(10,exp);
	}
}

int mgetline(char s[], int lim) {
	int c,i;
	
	for(i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i) {
		s[i] = c;
	}
	
	if(c == '\n') {
		s[i++] = c;
	}
	
	s[i] = '\0';
}

int power(int base, int exp) {
	int power;
	power = 1;
	while(exp-- > 0) {
		power *= base;
	}
	return power;	
}