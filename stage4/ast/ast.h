#ifndef AST_H
#define AST_H

#include <stdio.h>

// X-Macro: Define all node types in one place
// When adding a new node type, just add it here and both
// the enum and nodeTypeToString() will automatically include it
#define NODE_TYPES                                                             \
  X(VAR_NODE)                                                                  \
  X(OP_NODE)                                                                   \
  X(CONN_NODE)                                                                 \
  X(ASSG_NODE)                                                                 \
  X(READ_NODE)                                                                 \
  X(WRITE_NODE)                                                                \
  X(CONST_NODE)                                                                \
  X(IF_NODE)                                                                   \
  X(IFELSE_NODE)                                                               \
  X(WHILE_NODE)                                                                \
  X(BREAK_NODE)                                                                \
  X(CONTINUE_NODE)                                                             \
  X(REPEAT_NODE)                                                               \
  X(DOWHILE_NODE)                                                              \
  X(TYPE_NODE)                                                                 \
  X(DECL_NODE)                                                                 \
  X(STRCONST_NODE)                                                             \
  X(ARR_NODE)

// Generate the enum from NODE_TYPES
typedef enum {
#define X(name) name,
  NODE_TYPES
#undef X
} NodeType;

typedef struct tnode {
  int val;       // value of a number for NUM nodes.
  int type;      // type of variable  --(Integer only for stage2)
  char *varname; // name of a variable for ID nodes
  int nodetype;  // information about non-leaf nodes - read/write/connector/+/*
  struct Gsymbol
      *Gentry; // pointer to GST entry for global variables and functions
  struct tnode *left, *mid, *right; // left, mid, and right branches
} tnode;

struct tnode *makeConnectorNode(struct tnode *l, struct tnode *r);
struct tnode *makeAssgNode(struct tnode *l, struct tnode *r);
struct tnode *makeReadNode(struct tnode *l);
struct tnode *makeWriteNode(struct tnode *l);
struct tnode *makeVariableLeafNode(char *c);
struct tnode *makeDeclVariableNode(char *c);
struct tnode *makeIfNode(struct tnode *l, struct tnode *r);
struct tnode *makeIfElseNode(struct tnode *l, struct tnode *m, struct tnode *r);
struct tnode *makeWhileNode(struct tnode *l, struct tnode *r);
struct tnode *makeBreakLeafNode();
struct tnode *makeContinueLeafNode();
struct tnode *makeRepeatNode(struct tnode *l, struct tnode *r);
struct tnode *makeDoWhileNode(struct tnode *l, struct tnode *r);
struct tnode *makeTypeLeafNode(int var_type);
struct tnode *makeDeclNode(struct tnode *l, struct tnode *r);
struct tnode *makeStringConstantLeafNode(char *str);
struct tnode *makeDeclArrNode(char *arr_name, int size);

/*Create a node tnode*/
struct tnode *createTree(int val, int type, char *c, struct tnode *l,
                         struct tnode *r);

// Convert NodeType enum to string
const char *nodeTypeToString(int nodetype);

#endif