//Mgiuel Tirado Read char program 
#include <stdio.h>
// Note that EOF means that the program is waiting for the user to press CTRL+C to indicate End Of File
int main() {
	int c;
	/*Please note that C must be decalred as type int beucase a char value would not be big enouph 
	  to hold any value that get char returns. Cant use char becuase c must be big enouph to hold 
	  the value of EOF and any additional char values*/
	while((c = getchar()) != EOF) {
		putchar(c);
	}
	printf("The value for EOF is: %d",EOF);
	return 0;
}