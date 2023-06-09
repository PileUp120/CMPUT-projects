#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Make a strncpy ourselves 


// a strncpy clone (man strncpy)
// len is the maximum number of chars to copy including nul
void myStrncpy(char * dest, const char * src, const int len) {
  for (int i = 0 ; i < len && src[i]; i++) {
    dest[i] = src[i];
  }
}

#define N 64
#define NLETTERS 26
#define THELETTERA 'A'
int main() {
  char * bufferHeap = malloc(N*sizeof(char));
  memset(bufferHeap, THELETTERA, N*sizeof(char));
  char bufferStack[N] = { THELETTERA };

  // initialize 
  for (int i = 0 ; i < N - 1; i++) {
    char newLetter = (char)(THELETTERA + i % NLETTERS);
    bufferStack[i] = newLetter;
  }
  
  myStrncpy(bufferHeap, bufferStack, N);
  printf("BufferStack:\t %s\n", bufferStack);
  printf("BufferHeap:\t %s\n", bufferHeap);
  free(bufferHeap);
  return 0;
}
