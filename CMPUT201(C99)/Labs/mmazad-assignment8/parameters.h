// Implement a guard
#ifndef _PARAMETERS_H_

#define _PARAMETERS_H_
ParameterDef doubleParameterDef( char * name );

ParameterDef longParameterDef(   char * name );

ParameterDef stringParameterDef( char * name );

ParameterDef charParameterDef(   char * name );

ParameterDef mkParameterDef(   char * name, TypeFlag flag );

bool         equalParameterDef(  ParameterDef param1, ParameterDef param2);

Parameter    mkDoubleParameter(  ParameterDef def, double value);

Parameter    mkLongParameter(    ParameterDef def, long   value);

Parameter    mkStringParameter(  ParameterDef def, char * value);

Parameter    mkCharParameter(    ParameterDef def, char   value);

char *       nameParameter(      Parameter param );

TypeFlag     typeParameter(      Parameter param );

double       doubleParameter(    Parameter param );

long         longParameter(      Parameter param );

char *       stringParameter(    Parameter param );

char         charParameter(      Parameter param );

bool         equalParameter(     Parameter param1, Parameter param2);

void printParams(Parameter * params, size_t size);

#endif

#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>

enum type_flag {
  LONG,
  DOUBLE,
  STRING,
  CHAR,
};

typedef enum type_flag TypeFlag;

union any_t {
  int64_t aLong;
  double aDouble;
  char * aString;
  char aChar;
};

typedef union any_t Any;

struct parameter_def {
  char * name;
  TypeFlag type;
};

typedef struct parameter_def ParameterDef;

struct parameter_t {
  ParameterDef def;
  Any any;
};

typedef struct parameter_t Parameter;

// create a parameter def for aDouble
ParameterDef doubleParameterDef( char * name );
// create a parameter def for aLong
ParameterDef longParameterDef(   char * name );
// create a parameter def for aString
ParameterDef stringParameterDef( char * name );
// create a parameter def for aChar
ParameterDef charParameterDef(   char * name );
// create a parameter def for aChar
ParameterDef mkParameterDef(   char * name, TypeFlag flag );

// Are param1 and param2 equal?
bool         equalParameterDef(  ParameterDef param1, ParameterDef param2);

// create a double parameter 
Parameter    mkDoubleParameter(  ParameterDef def, double value);
// create a long parameter 
Parameter    mkLongParameter(    ParameterDef def, long   value);
// create a string parameter 
Parameter    mkStringParameter(  ParameterDef def, char * value);
// create a char parameter 
Parameter    mkCharParameter(    ParameterDef def, char   value);
// return the name of a parameter's def
char *       nameParameter(      Parameter param );
// return the type of a parameter from its def
TypeFlag     typeParameter(      Parameter param );
// return the double value of a parameter
double       doubleParameter(    Parameter param );
// return the long value of a parameter
long         longParameter(      Parameter param );
// return the string value of a parameter
char *       stringParameter(    Parameter param );
// return the char value of a parameter
char         charParameter(      Parameter param );
// Are param1 and param2 equal?
bool         equalParameter(     Parameter param1, Parameter param2);
// Print parameters!
void printParams(Parameter * params, size_t size);

ParameterDef doubleParameterDef( char * name )
{
    ParameterDef param;
    param.type = DOUBLE;
    param->name = name;
    
}

ParameterDef longParameterDef( char * name )
{
    ParameterDef param;
    param.type = LONG;
    param->name = name;
    
}ParameterDef stringParameterDef( char * name )
{
    ParameterDef param;
    param.type = STRING;
    param->name = name;
    
}ParameterDef charParameterDef( char * name )
{
    ParameterDef param;
    param.type = CHAR;
    param->name = name;
    
}