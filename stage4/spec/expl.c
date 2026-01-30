#include "expl.h"

const char *typeToString(int type) {
  switch (type) {
  case INT_TYPE:
    return "int";
  case STR_TYPE:
    return "str";
  case BOOL_TYPE:
    return "bool";
  case VOID_TYPE:
    return "void";
  default:
    return "unknown";
  }
}