#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int setAt(int anArray[], int arrLen, int position, int value) 
{
    if((position > (arrLen - 1)) || (position < 0))
    {
        return -1;
    }
    else
    {
        anArray[position] = value;
        return position;
    }
}

int *subArrPointer(const int anArray[], int arrLen, int position, int size) 
{
    if(position < 0)
    {
        return NULL;
    }
    else if(position > (arrLen - 1))
    {
        return NULL;
    }
    else if((position + size) > arrLen)
    {
        return NULL;
    }
    else
    {
        size_t memory = size * sizeof(int);
        int* subArray = malloc( memory );
        assert(subArray!=NULL);
        memset((void*)subArray, 0, memory);
        for (int i=0; i<size; i++)
        {
            subArray[i] = anArray[position];
            position++ ;
            
        }
    return subArray;
    }
}

int* insert(const int anArray[], int arrLen, int position, int value) 
{
    if((position > arrLen)||(position < 0))
    {
        return NULL;
    }
    else
    {
        size_t memory = (arrLen + 1) * sizeof(int);
        int* insertedArray = malloc( memory );
        assert(insertedArray!=NULL);
        memset((void*)insertedArray, 0, memory);
        if (position == arrLen)
        {
            for (int i=0; i<(arrLen-1); i++)
            {
                insertedArray[i] = anArray[i];
            }
            insertedArray[position] = value;
        }
        else
        {
            for (int i=0; i<(position); i++)
            {
                insertedArray[i] = anArray[i];
            }
            insertedArray[position]=value;
            for (int j=(position+1);j<(arrLen+1);j++)
            {
                insertedArray[j] = anArray[j-1];
            }
        }
    return insertedArray;
  }
  
}

int* erase(const int anArray[], int arrLen, int position) 
{
    if ((position > (arrLen -1))||(position < 0))
    {
    return NULL;
    }
    else
    {
        size_t memory = (arrLen-1) * sizeof(int);
        int* erasedArray = malloc( memory );
        assert(erasedArray!=NULL);
        memset((void*)erasedArray, 0, memory);
        if (position == arrLen)
        {
            for (int i=0; i<(arrLen-2); i++)
            {
                erasedArray[i] = anArray[i];
            }
            
        }
        else
        {
            for (int i=0; i<(position); i++)
            {
                erasedArray[i] = anArray[i];
            }
            for (int j=position;j<(arrLen-1);j++)
            {
                erasedArray[j] = anArray[j+1];
            }
    }

    return erasedArray;
  }
 
}

/////////////////////////////////////////////////////
// This is all driver code, please don't modify it.//
/////////////////////////////////////////////////////

const char * indexOutOfBounds = "\nIndex out of bounds..";

void printArray(int * anArray, int arrLen) {
  for(int idx=0; idx < arrLen; idx++) {
    printf("%d ", anArray[idx]);
  }
  printf("\n");
}

void checkInput(int err) {
  if (!err || err == EOF) {
    printf("\nInvalid input!\n");
    exit(1);
  }
}

void evaluateSetAt(int * anArray, int arrLen) {
  int position = -1;
  int value    = -1;
  printf("Enter index and value to set at index: ");
  checkInput(scanf("%d", &position));
  checkInput(scanf("%d", &value));
  if (-1==setAt(anArray, arrLen, position, value)) {
    puts(indexOutOfBounds);
  }
  printf("Updated array: ");
  printArray(anArray, arrLen);  
}

void evaluateSubArrPointer(int * anArray, int arrLen) {
  int position = -1;
  int size     = -1;
  printf("Enter starting index and size of sub-array: ");
  checkInput(scanf("%d",&position));
  checkInput(scanf("%d",&size));
  int *ptr = subArrPointer(anArray, arrLen, position, size);
  if (ptr==NULL) {
    puts(indexOutOfBounds);
  } else {
    printf("Sub-array: ");
    printArray(ptr,size);
    free(ptr);
  }
}

int * evaluateInsert(int * anArray, int arrLen, int * resLen) {
  int anotherValue=  0;
  int position    = -1;
  printf("Enter index and value to insert at index: ");
  checkInput(scanf("%d", &position));
  checkInput(scanf("%d", &anotherValue));
  int *retArray = insert( anArray, arrLen, position, anotherValue);
  if(retArray==NULL) {
    // failed insert
    puts(indexOutOfBounds);
    *resLen = arrLen;
    return anArray;
  }
  printf("\nArray after insertion: ");
  printArray(retArray, arrLen+1);
  *resLen = arrLen+1;
  return retArray;
}

void evaluateDeletion(int * anArray, int arrLen) {
  int position = -1;
  printf("Enter index to delete: ");
  checkInput(scanf("%d",&position));
  int * eraseArray = erase(anArray, arrLen, position);
  if(eraseArray==NULL) {
    puts(indexOutOfBounds);
  } else {
    printf("\nAfter erasing: ");
    printArray(eraseArray, arrLen-1);
    free(eraseArray);
  }
}

int * testAllocArray(int arrLen) {
  size_t size = arrLen * sizeof(int);
  int* array = malloc( size );
  assert(array!=NULL);
  memset((void*)array, 0, size);
  for(int idx=0; idx<arrLen; idx++) {
    array[idx] = idx;
  }
  return array;
}

/* Unit tests for setAt you need to pass
 *
 */
void testSetAt() {
  const int arrLen = 200;
  int* array = testAllocArray(arrLen);
  for(int idx=0; idx<arrLen; idx++) {
    // test if the return value is correct
    assert(idx == setAt(array, arrLen, idx, idx));
    // test if the value was set
    assert(array[idx] == idx);
  }
  assert(setAt(array,arrLen,-1,0)==-1);
  assert(setAt(array,arrLen,-1000,0)==-1);
  assert(setAt(array,arrLen,arrLen,0)==-1);
  assert(setAt(array,arrLen,arrLen+10,0)==-1);   
  assert(setAt(array,arrLen,arrLen-1,0)==arrLen-1);   
  free(array);
}

void assertCompareArrays(const int * array1, const int * array2, int arrLen) {
  for(int idx=0; idx<arrLen; idx++) {
    assert(array1[idx] == array2[idx]);
  }
}

/* Unit tests for subArrPointer you need to pass
 *
 */
void testSubArrPointer() {
  const int arrLen = 200;
  int* array = testAllocArray(arrLen);
  // verify it can copy a whole array
  int * arrayCopy = subArrPointer( array, arrLen, 0, arrLen );
  assert(arrayCopy != NULL);
  assert(arrayCopy != array);
  assert(&arrayCopy[0] != &array[0]);
  assertCompareArrays(array,arrayCopy,arrLen);
  const int offset = 10;
  int * arrayCopy2 = subArrPointer( array, arrLen, arrLen-offset, offset );
  assert(arrayCopy2 != NULL);
  assertCompareArrays( arrayCopy2, &array[arrLen-offset], offset);
  assert( subArrPointer( array, arrLen, 0, arrLen+1 ) == NULL);
  assert( subArrPointer( array, arrLen, -1, arrLen ) == NULL);
  free(array);
  free(arrayCopy);
  free(arrayCopy2);
}

/* Unit tests for subArrPointer you need to pass
 *
 */
void testInsert() {
  const int arrLen = 200;
  int* array = testAllocArray(arrLen);
  // verify it insert at the front
  int * arrayCopy = insert( array, arrLen, 0, -1 );  
  assert(arrayCopy != NULL);
  assert(arrayCopy != array);
  assert(&arrayCopy[0] != &array[0]);
  assert(arrayCopy[0] == -1);
  assert(arrayCopy[1] == 0);
  assert(arrayCopy[arrLen] == arrLen-1);
  assertCompareArrays(array,arrayCopy+1,arrLen);

  int * arrayCopy2 = insert( arrayCopy, arrLen+1, arrLen+1, -1 );
  assert(arrayCopy2 != NULL);
  assert(arrayCopy2[arrLen+1] == -1);
  free(array);
  free(arrayCopy);
  free(arrayCopy2);
}

void testErase() {
  const int arrLen = 200;
  int* array = testAllocArray(arrLen);
  for (int i = 0; i < arrLen ; i++) {
    int * newArray = erase(array, arrLen - i, 0);
    assert(newArray != array);
    if (arrLen - i > 1) {
      // if arrLen - i == 1 then newArray is of size 0
      assert(newArray[0] != array[0]);
      assert(newArray[0] == array[1]);
    }
    free(array);
    array = newArray;
  }
  assert(NULL == erase(array, 0, 0));
  free(array);
}

#define N 20

int main() {
  int array[N]={0};
  for(int idx=0; idx<N; idx++) {
    array[idx]=idx;
  }
  printf("Original array: ");
  printArray(array,N);

  printf("SET-AT\n");
  evaluateSetAt(array, N);
  
  printf("SUB-ARRAY\n");
  evaluateSubArrPointer(array, N);
  
  printf("INSERTION\n");
  int retArrayLen = N;
  int * retArray = evaluateInsert(array, N, &retArrayLen);
  
  printf("DELETION\n");
  evaluateDeletion(retArray, retArrayLen);

  if (retArray!=NULL && retArray != array) {
    free(retArray);
  }
  testSetAt();
  testSubArrPointer();
  testInsert();
  testErase();
  return 0;  
}
