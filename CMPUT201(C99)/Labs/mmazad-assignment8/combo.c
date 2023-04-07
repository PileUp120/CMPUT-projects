#include "combo.h"
#include "parameters.h"
#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

// implement all of combo.h

struct combo_t {
  // IMPLEMENT 
};

/* end:solution*/

Combo createParameterCombo() {
  // IMPLEMENT

}
void addParameterDefCombo(Combo combo, ParameterDef def) {
  // IMPLEMENT
size_t addParameterCombo(Combo combo, Parameter param) {
  // IMPLEMENT
}
size_t nParamsCombo(Combo combo) {
  // IMPLEMENT
}
bool hasNextCombo(Combo combo) {
  // IMPLEMENT
}



Parameter * nextCombo(Combo combo) {  
  // IMPLEMENT
}

void freeParamsCombo(Combo combo, Parameter * params) {
  if (combo==NULL) {
    abort();
  }
  free(params);
}
void freeCombo(Combo combo) {
  // IMPLEMENT

}
