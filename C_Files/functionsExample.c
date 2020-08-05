//Miguel tirado C functions 1.7
#include <stdio.h> 

/* test power function */
int power(int m, int n);

int main(void) { 
	int i; 
	
	for(i = 0; i < 10; ++i) {
		printf("i value: %d, power1: %d, power2: %d\n",i,power(2,i),power(3,i));
	}
}

/* power: raise base to n-th power: n>= 0 */
int power(int base, int n) {
	int i, p;
	p = 1;
	for(i = 1; i <= n; ++i) {
		p = p * base; 
	}
	return p;
}
