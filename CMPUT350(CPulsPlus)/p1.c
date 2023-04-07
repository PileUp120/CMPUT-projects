// C code

#include <stdio.h>
#include <assert.h>

// sort array A with n elements
// into non-decreasing order  
// precond: n > 0
void simple_sort(int A[], int n)
{
  assert(n > 0);
  int i;
  for (i=n-1; i >= 1; --i) {
    // find maximum element in A[0..i] 
    int max_j = 0;
    int j;
    for (j=1; j <= i; ++j) {
      if (A[j] > A[max_j]) {
        max_j = j;
      }
    }
    // swap A[i] and A[max_j]  
    int t = A[i];
    A[i] = A[max_j];
    A[max_j] = t;
  }
}

int main()
{
  // test code

  const int N = 10;
  int A[N];

  // populate array with N-1..0
  int i;
  for (i=0; i < N; ++i) {
    A[i] = N-1-i;
  }

  // sort it
  simple_sort(A, N);

  // print it
  for (i=0; i < N; ++i) {
    printf("%d %d\n", i, A[i]);
  }
  
  // should be: 0 ... N-1
  return 0;
}
