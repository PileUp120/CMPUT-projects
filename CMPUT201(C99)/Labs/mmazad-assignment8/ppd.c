#include "parameters.h"
#include "ppd.h"
#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

// A growing array implementation

PPDArray createPPDArray() {
  PPDArray ppd_array = malloc(sizeof(struct coolbearlist));
  ppd_array->list = NULL;
  ppd_array->size = 0;
  return ppd_array;
}
size_t sizePPDArray(PPDArray array) {
  return array->size;
}
void freePPDArray(PPDArray array) {  
  if(array->params!=NULL) {
    free(array->params);
  }
  free(array);
}
void freeArrayPPDArray(PPDArray array) {
  // IMPLEMENT
}


ParameterDef parameterDefPPDArray(PPDArray array, size_t index) {
  assert(index < array->size);
  return array->params[index].def;
}

ParameterDef * parameterDefRefPPDArray(PPDArray array, size_t index) {
  assert(index < array->size);
  return &(array->params[index].def);
}


Parameter parameterPPDArray(PPDArray array, size_t index) {
  assert(index < array->size);
  return array->params[index].param;
}

PPDArray arrayPPDArray(PPDArray array, size_t index) {
  assert(index < array->size);
  return array->params[index].array;
}


void addPPDPPDArray(PPDArray array, PPD defOrParam) {
  // IMPLEMENT
}
void addDefPPDArray(PPDArray array, ParameterDef def) {
  addPPDPPDArray(array, (PPD){.def=def});
}
void addParamPPDArray(PPDArray array, Parameter param) {
  addPPDPPDArray(array, (PPD){.param=param});
}
void addPPDArrayPPDArray(PPDArray array, PPDArray newArray  ) {
  addPPDPPDArray(array, (PPD){.array=newArray});
}
void addInt64PPDArray(PPDArray array, int64_t int64  ) {
  addPPDPPDArray(array, (PPD){.int64=int64});
}
void addStringPPDArray(PPDArray array, char * str ) {
  addPPDPPDArray(array, (PPD){.str=str});
}

int64_t int64PPDArray(PPDArray array, size_t index) {
  assert(index < array->size);
  return array->params[index].int64;
}
char * stringPPDArray(PPDArray array, size_t index) {
  assert(index < array->size);
  return array->params[index].str;
}

void setInt64PPDArray(PPDArray array, size_t index, int64_t value) {
  assert(index < array->size);
  // IMPLEMENT
}
