/* Miguel Tirado
 * Exercise 2-5 
 * write the function any(s1,s2) which returns the first location in the string
 * s1 where any character from the string s2 occurs, or -1 if s1 contains no 
 * characters from s2. (The standard library function strpbrk does 
 * the same job but returns a pointer to the location*/
 
 #include <stdio.h>
 #define MAXLINE 1000
 
 int mgetline(char line[], int maxline);
 int any(char s1[], char s2[]);
 
 int main(void) {
	 char s1[MAXLINE],s2[MAXLINE];
	 int val;
	 
	 mgetline(s1,MAXLINE);
	 
	 mgetline(s2,MAXLINE);
	 val = any(s1,s2);
	 printf("%d",val);
	 
 }
 int mgetline(char s[], int lim) {
	 int i,c;
	 for(i = 0; i < lim-1 && (c=getchar()) != EOF && c!= '\n'; ++i) {
		 s[i] = c;
	 }
	 if (c == '\n') {
		 s[i++] = c;
	 }
	 //Ends the char array 
	 s[i] = '\0';
 }
 int any(char s1[], char s2[]) {
	 int i,j,check_next_char;
	 
	 check_next_char = 1;
	 
	 for(i = 0; s1[i] != '\0' && (check_next_char);) {
		 for(j=0; s2[j] != '\0' && (s1[i]!=s2[j]);++j) 
			 ;
		 if(s2[j] == '\0') {
			 check_next_char = 1;
			 i++; // go for the next char in s1
		 } else {
			 check_next_char = 0;//match found 
		 }
		 
	 }
	 if(s1[i] == '0') {
		 return -1;
	 } else {
		 return i;
	 }
 }