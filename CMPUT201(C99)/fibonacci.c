#include <stdio.h>

int main(int argc, char ** argv) {
	unsigned long prevprev = 1;
	unsigned long prev = 1;
	unsigned long next;
	unsigned long stop;
	printf("How many iterations? ");
	scanf("%lu", &stop);
	printf("i=0: %lu\n", prevprev);
	printf("i=1: %lu\n", prev);
	for (unsigned long i = 2; i <= stop; i++) {
		next = prevprev + prev;
		if (next < prev){
			printf("I ran out of bits!\n");
			break;
		}
		printf("i=%lu: %lu\n", i, next);
		prevprev = prev;
		prev = next;
	}
	return 0;
}
