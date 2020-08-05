#include <stdio.h>

int main () {
	int c, n1,n2,n3;
	
	n1 = 0;
	while((c = getchar()) != EOF) {
		if (c == '\n') {
			++n1;
		}
		if (c == ' ') {
			++n2;
		}
		if (c == '	') {
			++n3;
		}
	}
	printf("\nNew Lines: %d Spaces: %d Tabs: %d\n",n1,n2,n3);
	return 0;
}