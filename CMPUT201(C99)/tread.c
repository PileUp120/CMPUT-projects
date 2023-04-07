#include <stdio.h>

int main() {

	int i, j;
	float x, y;

	scanf("%d%d%f%f", &i, &j, &x, &y);
	printf("i = %d,\n j = %d,\n x = %f,\n y = %f,\n x + y = %f\n",
		i, j, x, y, x+y);

	return 0;
}
