/*

  CMPUT201W20 Midterm 3 Question 3
  
  This program attempts to create a growing list of coolbears.
  Coolbears have names, metadata (junk), and temperatures. We want to
  add test bears and iterate through them and calculate their average
  temperature. But something is wrong and the program doesn't work.
  I changed only 2 lines.

  NAME:Mohammed Azad
  CCID:mmazad
  STUDENT NUMBER:1481693

  In this comment please describe how you fixed this problem and what
  tools you used:Changed type of i in both (int16_t i = NBEARS-1; i >= 0; i--) 
  and (size_t i = NBEARS-1; i >= 0; i--) to int, from int16_t and size_t
  respectively. Using Makefile, it said there is an overflow in int16_t that changes
  i from 32999 to -32537, and for size_t it said "comarison of unsigned 
  expression >=0 is always true".

 */
#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#define METADATA 128

struct coolbear {
  const char * name;
  long int temperature;
  char metadata[METADATA];
};
typedef struct coolbear * CoolBear;

struct coolbearlist {
  struct coolbear * list;
  size_t ncoolbears;
};
typedef struct coolbearlist * CBList;

CBList createCBList() {
  CBList cblist = malloc(sizeof(struct coolbearlist));
  cblist->list = NULL;
  cblist->ncoolbears = 0;
  return cblist;
}
void freeCBList(CBList cblist) {
  free(cblist->list);
  free(cblist);
}

CoolBear getCoolbearCBList(CBList cblist, size_t index) {
  return &cblist->list[index];
}

void addCoolBearCBList(CBList cblist, struct coolbear coolbear) {
  assert(cblist != NULL);
  size_t ncoolbears = cblist->ncoolbears;
  cblist->list = realloc(cblist->list, (ncoolbears+1)*sizeof(coolbear));
  assert(cblist->list != NULL);
  cblist->list[ncoolbears] = coolbear;
  cblist->ncoolbears++;
}
#define NAMES 4
const char * names[] = {
  "Olivia",
  "Daryl",
  "Charmane",
  "Lin"
};
#define TEMPS 5
const long int temps[] = {
  -10,
  -20,
  -30,
  -40,
  -50,
};
#define NBEARS 33000


// Verify that the cblist temperatures
// are what we expected.
void checkTemperature( CBList cblist);

int main() {
  CBList cblist = createCBList();
  // We'll make lots of coolbears!
  for (size_t i = 0; i < NBEARS; i++) {
    addCoolBearCBList( cblist, (struct coolbear){
        .name=names[i%NAMES],
        .temperature=temps[i%TEMPS]}
    );    
  }
  // Ensure we have NBEARS coolbears in cblist
  assert(cblist->ncoolbears == NBEARS); // DNC
  // Now we're calculate the average temperature of a coolbear!
  long int temperatureSum = 0;  
  for (int i = NBEARS-1; i >= 0; i--) {
    CoolBear bear = getCoolbearCBList(cblist, i);
    temperatureSum += bear->temperature;
  }
  long int averageTemp = temperatureSum / NBEARS;
  // Assert that our average is bounded between the
  // the smallest and largest temperatures
  assert(averageTemp < temps[0]); // DNC
  assert(averageTemp > temps[4]); // DNC

  checkTemperature( cblist );
  
  freeCBList(cblist);
  return 0;
}

// Verify that the cblist temperatures
// are what we expected.
void checkTemperature( CBList cblist) {
  size_t count = 0;
  // Now we'll see if the temperatures were properly set.
  for (int i = NBEARS-1; i >= 0; i--) {
    // check that the coolbears temperatures didn't change
    assert( getCoolbearCBList( cblist, i)->temperature == temps[i%TEMPS] );// DNC
    count++; // DNC
  }
  // assert that we checked over NBEARS coolbears
  assert(count == NBEARS); // DNC
}
