//Miguel Tirado Temp converter with floating point values 
#include <stdio.h>

int main() {
	float fahr, celsius;
	int lower,upper, step;
	
	lower = 0;
	upper = 300;
	step = 20;
	
	fahr = lower;
	printf("|Farenheit|  |Celsius|\n");
	while(fahr <= upper) {
		//Note if i use (5/9) here i will get 0 becuase the compiler truncates the int to zero 
		celsius = (5.0/9.0) * (fahr - 32.0);
		printf("   %3.0f        %6.1f\n",fahr,celsius);
		fahr = fahr + step;
	}
	
	printf("-----------------------------------\n");
	
	fahr = upper;
	while(fahr >= lower) {
		celsius = (5.0/9.0) * (fahr - 32.0);
		printf("   %3.0f        %6.1f\n",fahr,celsius);
		fahr = fahr - step;
	}
	return 0;
}