/* Prints int and float values in various formats */

#include <stdio.h>

int main(void) {

	int i;
	float x;

	i = 40;
	x = 1000839.21f;

	printf("|%f|%5d|%-5d|%5.3d|\n", i, i, i, i);
	printf("|%d|%10.3f|%10.3e|%-10g|\n", x, x, x, x);

	return 0;
}
