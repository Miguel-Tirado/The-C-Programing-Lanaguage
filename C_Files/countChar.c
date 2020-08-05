//Miguel Tirado count character inputs 
#include <stdio.h>

int main() {
	long nc;
	
	nc = 0;
	while(getchar() != EOF) {
		++nc;
	}
	printf("%1d\n",nc);
	return 0;
}