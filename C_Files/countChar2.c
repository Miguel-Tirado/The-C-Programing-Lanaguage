#include <stdio.h>

int main() {
	double nc;
	// Note that the semicolon below is intentiall for the C langauge to indicate a null statement
	// the for statment must have a body 
	for(nc = 0; getchar() != EOF; ++nc)
		;
	printf("%.0f\n",nc);
	return 0;
}