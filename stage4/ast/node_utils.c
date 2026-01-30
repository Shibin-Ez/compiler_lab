#include "ast.h"

// Generate the string conversion using the same NODE_TYPES macro
const char *nodeTypeToString(int nodetype) {
  switch (nodetype) {
#define X(name)                                                                \
  case name:                                                                   \
    return #name;
    NODE_TYPES
#undef X
  default:
    return "UNKNOWN_NODE";
  }
}
