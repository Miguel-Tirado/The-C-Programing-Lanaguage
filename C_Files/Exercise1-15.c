// Miguel Tirado Rewritten section 1.2 ex using function
#include <stdio.h>
void temp(int initial, int final);
/*print Fahrenheit-Celsius table for fahr = 0, 20, ..., 300 */
int main (void) {
	int fahr,celsius;
	int lower,upper,step;
	
	lower = 0;
	upper = 300;

	
	fahr = lower; 
	temp(fahr, upper);
}

void temp(int start, int end) {
	int celsius;
	int	step = 20; 
	while (start <= end) {
		celsius = 5 * (start-32) /9;
		printf("%d\t%d\n", start, celsius);
		start = start + step;
	}
}