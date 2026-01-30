#ifndef EXPL_H
#define EXPL_H

typedef enum {
  VOID_TYPE,
  INT_TYPE,
  BOOL_TYPE,
  STR_TYPE
} VarType;

const char *typeToString(int type);

#endif