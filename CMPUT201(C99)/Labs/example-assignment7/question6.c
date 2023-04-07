#include <stdio.h>
#include <stdlib.h>
// print in rows of 5, 99 to 0


#define N (5*20)
#define BASE 5
int main() {
  int * myIntegers = malloc( N * sizeof(int) );
  for (int i = N-1; i > 0; i--) {
    myIntegers[N-1-i] = i;
  }
  int * ints = myIntegers;
  for (int i = 0; i < N / BASE; i++) {
    printf("%d %d %d %d %d\n", *ints++, *ints++, *ints++, *ints++, *ints++);
  }
}
