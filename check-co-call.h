#ifndef CHECK_CO_CALL_H_
#define CHECK_CO_CALL_H_

#include "gcc-plugin.h"
#include "gimple.h"
#include "tree-pass.h"

unsigned int check_for_co_call_violations(function* fun);

#endif
