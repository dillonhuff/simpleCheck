#include "check-co-call.h"

#include "diagnostic-core.h"

#include <string>

std::string funcNameStr(function* f) {
  const char* name = function_name(f);
  std::string callName(name);
  return callName;
}

int is_funcall(std::string funcName, gimple stmt) {
  if (is_gimple_call(stmt)) {
    tree fn_decl = gimple_call_fndecl(stmt);
    if (!fn_decl) {
      return 0;
    }
    const char* name = function_name(DECL_STRUCT_FUNCTION(fn_decl));
    std::string callName(name);
    return callName == funcName;
  }
  return 0;
}

int calls_fn(std::string fnName, function* fun) {
  basic_block bb;
  gimple stmt;
  gimple_stmt_iterator gsi;
  FOR_EACH_BB_FN(bb, fun) {
    for (gsi = gsi_start_bb(bb); !gsi_end_p(gsi); gsi_next(&gsi)) {
      stmt = gsi_stmt(gsi);
      if (is_funcall(fnName, stmt)) {
	return 1;
      }
    }
  }
  return 0;
}

int co_call_violation(std::string fnName1, std::string fnName2, function* fun) {
  int locks = calls_fn(fnName1, fun);
  int unlocks = calls_fn(fnName2, fun);
  return locks && !unlocks;
}

unsigned int check_for_co_call_violations(function* fun) {
  if (co_call_violation("rcu_read_lock", "rcu_read_unlock", fun)) {
    std::string warnSuffix = " calls rcu_read_lock, but does not call rcu_read_unlock";
    std::string warningStr = funcNameStr(fun) + warnSuffix;
    warning_at(0, 0, warningStr.c_str());
  }
  return 0;
}
