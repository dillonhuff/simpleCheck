#include "gcc-plugin.h"
#include "tree-pass.h"
#include "function.h"

#include <iostream>

using namespace std;

int plugin_is_GPL_compatible;

extern "C"
unsigned int
check_co_call_execute() {
  return 0;
}

extern "C"
bool
check_co_call_gate() {
  return true;
}

static struct opt_pass check_func_co_call_pass = {
  GIMPLE_PASS,
  "checkcocallingpassing",
  0,
  check_co_call_gate,
  check_co_call_execute,
};

extern "C"
int
plugin_init (plugin_name_args* plugin_info,
             plugin_gcc_version* ver) {
  struct register_pass_info pass_info;
  pass_info.pass = &check_func_co_call_pass;
  const char* ref_pass_name = "ssa";
  pass_info.reference_pass_name = ref_pass_name;
  pass_info.ref_pass_instance_number = 1;
  pass_info.pos_op = PASS_POS_INSERT_AFTER;

  register_callback(plugin_info->base_name,
		    PLUGIN_PASS_MANAGER_SETUP,
		    NULL,
		    &pass_info);

  return 0;
}
