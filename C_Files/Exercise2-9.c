/* Exercise 2.9 twos compliment number system 
 * x &= (x-1) deletes the rightmost 1-bit in x. */
 
#include <stdio.h>

int bitcount(unsigned x);

int main (void) {
	//here we are casting 12 to be unsigned 
	printf("%d",bitcount((unsigned)12));
}

int bitcount(unsigned x) {
	int b;
	
	for(b = 0; x != 0; x &= x - 1) {
		++b;
	}
	return b;
}