#include <stdio.h>

int main(void){
	int i,month,day;
	month = 2;
	int x = 31;
	for(i = 1; i < month; i++) {
		day += x;
		printf("day: %d and i: %d\n",day, i);
	}
}