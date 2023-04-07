#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_SEED 1
#define DEFAULT_COEFFECIENT1 1234567891
#define DEFAULT_COEFFECIENT2 987654321
const uint64_t MODULUS_CONSTANT = 10;
const uint64_t DEFAULT_NUMBERS = 1;

uint64_t coeffecient1 = DEFAULT_COEFFECIENT1;
uint64_t coeffecient2 = DEFAULT_COEFFECIENT2;

// Don't change anything above this line



// Your code goes here



// Don't change anything below this line

uint64_t input_u64(uint64_t default_value) {
    /* Read a u64 from the input, (user or file)
     * using default_value instead if the user enters 0
     */
    uint64_t input_value = 0;
    int scanned = scanf("%llu", (long long unsigned int *) &input_value);
    if (scanned != 1) {
        abort();
    }
    if (input_value == 0) {
        return default_value;
    }
    return input_value;
}

int main() {
  printf("What is the seed?\n");
  uint64_t input_seed = input_u64(DEFAULT_SEED);

  printf("What is coeffecient1?\n");
  uint64_t input_coeffecient1 = input_u64(DEFAULT_COEFFECIENT1);

  printf("What is coeffecient2?\n");
  uint64_t input_coeffecient2 = input_u64(DEFAULT_COEFFECIENT2);

  printf("How many numbers?\n");
  uint64_t numbers = input_u64(DEFAULT_NUMBERS);

  seedMyRand(input_seed, input_coeffecient1, input_coeffecient2);

  for (uint64_t number = 0 ; number < numbers; number++) {
    printf("%llu\n", (unsigned long long) myRand() % MODULUS_CONSTANT);
  }

  return 0;
}
