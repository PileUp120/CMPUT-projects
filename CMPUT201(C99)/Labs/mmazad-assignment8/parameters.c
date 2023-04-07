#include "parameters.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Implement all of the parameter.h functions
ParameterDef mkParameterDef( char * name, TypeFlag flag ) {
  // IMPLEMENT
}

ParameterDef doubleParameterDef( char * name ) {
  // IMPLEMENT
}
ParameterDef longParameterDef(   char * name ) {
  // IMPLEMENT
}
ParameterDef stringParameterDef( char * name ) {
  // IMPLEMENT
}
ParameterDef charParameterDef(   char * name ) {
  // IMPLEMENT
}
Parameter    mkDoubleParameter( ParameterDef def, double value) {
  // IMPLEMENT
}
Parameter    mkLongParameter(   ParameterDef def, long   value) {
  // IMPLEMENT
}
Parameter    mkStringParameter( ParameterDef def, char * value) {
  // IMPLEMENT
}
Parameter    mkCharParameter(   ParameterDef def, char   value) {
  // IMPLEMENT
}

TypeFlag     typeParameter(      Parameter param ) {
  // IMPLEMENT
}
double       doubleParameter(    Parameter param ) {
  // IMPLEMENT
}
long         longParameter(      Parameter param ) {
  // IMPLEMENT
}
char *       stringParameter(    Parameter param ) {
  // IMPLEMENT
}
char         charParameter(      Parameter param ) {
  // IMPLEMENT
}
char *       nameParameter(      Parameter param ) {
  // IMPLEMENT
}

bool equalParameterDef(  ParameterDef param1, ParameterDef param2) {
  // IMPLEMENT
}

bool equalParameter(  Parameter param1, Parameter param2) {
  // IMPLEMENT
}

void printParam(Parameter param ) {
  TypeFlag type = param.def.type;
  switch((int)type) {
  case LONG:
    printf("%ld", param.any.aLong);
    break;
  case STRING:
    printf("%s", param.any.aString);
    break;
  case CHAR:
    printf("%c", param.any.aChar);
    break;
  case DOUBLE:
    printf("%g", param.any.aDouble);
    break;
  default:
    abort();
    break;
  }
}

void printParams(Parameter * params, size_t size) {
  for (size_t i = 0 ; i < size; i ++) {
    printParam(params[i]);
    printf(" ");
  }
  puts("");
}
