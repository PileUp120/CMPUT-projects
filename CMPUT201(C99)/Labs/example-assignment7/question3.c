#include <stdio.h>
#include <stdlib.h>

// Read a string to the stack and the heap and print it out


/* checkInput: given the result of scanf check if it 
 * 0 elements read or EOF. If so exit(1) with a warning.
 *
 */
void checkInput(int err) {
  if (!err || err == EOF) {
    printf("\nInvalid input!\n");
    exit(1);
  }
}

#define N 16
int main() {
  char bufferStack[N] = { '\0' };
  char * bufferHeap = calloc(N, sizeof(char));
  char junk[N];
  printf("Enter a string no more than 16 chars long\n0123456789012345\n");
  checkInput(scanf("%16[^\n]", bufferStack));
  printf("BufferStack: %s\n", bufferStack);
  checkInput(scanf("%16[\n]", junk));
  checkInput(scanf("%16[^\n]", bufferHeap));
  printf("BufferHeap: %s\n", bufferHeap);
  free(bufferHeap);
  return 0;
}
