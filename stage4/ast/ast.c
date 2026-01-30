#include "ast.h"
#include "../spec/expl.h"
#include "../symbol_table/symbol_table.h"
#include "../utility/error.h"
#include <stdlib.h>
#include <string.h>

struct tnode *makeConnectorNode(struct tnode *l, struct tnode *r) {
  struct tnode *temp;
  temp = (struct tnode *)malloc(sizeof(struct tnode));
  temp->varname = NULL;
  temp->type = VOID_TYPE;
  temp->nodetype = CONN_NODE;
  temp->left = l;
  temp->mid = NULL;
  temp->right = r;
  return temp;
}

struct tnode *makeAssgNode(struct tnode *l, struct tnode *r) {
  // Type checking
  if (l->type != r->type)
    report_error("Type mismatch on Assignment: %s cannot be assigned to %s\n",
                 typeToString(r->type), typeToString(l->type));

  struct tnode *temp;
  temp = (struct tnode *)malloc(sizeof(struct tnode));
  temp->varname = NULL;
  temp->type = VOID_TYPE;
  temp->nodetype = ASSG_NODE;
  temp->left = l;
  temp->mid = NULL;
  temp->right = r;
  return temp;
}

struct tnode *makeReadNode(struct tnode *l) {
  struct tnode *temp;
  temp = (struct tnode *)malloc(sizeof(struct tnode));
  temp->varname = NULL;
  temp->type = VOID_TYPE;
  temp->nodetype = READ_NODE;
  temp->left = l;
  temp->mid = NULL;
  temp->right = NULL;
  return temp;
}

struct tnode *makeWriteNode(struct tnode *l) {
  struct tnode *temp;
  temp = (struct tnode *)malloc(sizeof(struct tnode));
  temp->varname = NULL;
  temp->type = VOID_TYPE;
  temp->nodetype = WRITE_NODE;
  temp->left = l;
  temp->mid = NULL;
  temp->right = NULL;
  return temp;
}

// For variable usage in expressions - does Lookup
struct tnode *makeVariableLeafNode(char *c) {
  struct tnode *temp;
  temp = (struct tnode *)malloc(sizeof(struct tnode));
  temp->varname = strdup(c);
  temp->nodetype = VAR_NODE;
  temp->Gentry = Lookup(temp->varname);
  if (temp->Gentry == NULL)
    report_error("Use of undeclared variable: %s\n", temp->varname);
  temp->type = temp->Gentry->type; // Get type from symbol table
  temp->left = NULL;
  temp->mid = NULL;
  temp->right = NULL;
  return temp;
}

// For variable declarations - no Lookup (symbol table not built yet)
struct tnode *makeDeclVariableNode(char *c) {
  struct tnode *temp;
  temp = (struct tnode *)malloc(sizeof(struct tnode));
  temp->varname = strdup(c);
  temp->type = VOID_TYPE; // Type will be set during symbol table building
  temp->nodetype = VAR_NODE;
  temp->Gentry = NULL;
  temp->left = NULL;
  temp->mid = NULL;
  temp->right = NULL;
  return temp;
}

struct tnode *makeDeclArrNode(char *arr_name, int size) {
  struct tnode *temp;
  temp = (struct tnode *)malloc(sizeof(struct tnode));
  temp->varname = strdup(arr_name);
  temp->type = VOID_TYPE; // Type will be set during symbol table building
  temp->nodetype = ARR_NODE;
  temp->val = size; // Size is stored in the `val` field
  temp->Gentry = NULL;
  temp->left = NULL;
  temp->mid = NULL;
  temp->right = NULL;
  return temp;
}

struct tnode *makeIfNode(struct tnode *l, struct tnode *r) {
  struct tnode *temp;
  temp = (struct tnode *)malloc(sizeof(struct tnode));
  temp->varname = NULL;
  temp->type = VOID_TYPE;
  temp->nodetype = IF_NODE;
  temp->left = l;
  temp->mid = NULL;
  temp->right = r;
  return temp;
}

struct tnode *makeIfElseNode(struct tnode *l, struct tnode *m,
                             struct tnode *r) {
  struct tnode *temp;
  temp = (struct tnode *)malloc(sizeof(struct tnode));
  temp->varname = NULL;
  temp->type = VOID_TYPE;
  temp->nodetype = IFELSE_NODE;
  temp->left = l;
  temp->mid = m;
  temp->right = r;
  return temp;
}

struct tnode *makeWhileNode(struct tnode *l, struct tnode *r) {
  struct tnode *temp;
  temp = (struct tnode *)malloc(sizeof(struct tnode));
  temp->varname = NULL;
  temp->type = VOID_TYPE;
  temp->nodetype = WHILE_NODE;
  temp->left = l;
  temp->mid = NULL;
  temp->right = r;
  return temp;
}

struct tnode *makeBreakLeafNode() {
  struct tnode *temp;
  temp = (struct tnode *)malloc(sizeof(struct tnode));
  temp->varname = NULL;
  temp->type = VOID_TYPE;
  temp->nodetype = BREAK_NODE;
  temp->left = NULL;
  temp->mid = NULL;
  temp->right = NULL;
  return temp;
}

struct tnode *makeContinueLeafNode() {
  struct tnode *temp;
  temp = (struct tnode *)malloc(sizeof(struct tnode));
  temp->varname = NULL;
  temp->type = VOID_TYPE;
  temp->nodetype = CONTINUE_NODE;
  temp->left = NULL;
  temp->mid = NULL;
  temp->right = NULL;
  return temp;
}

struct tnode *makeRepeatNode(struct tnode *l, struct tnode *r) {
  struct tnode *temp;
  temp = (struct tnode *)malloc(sizeof(struct tnode));
  temp->varname = NULL;
  temp->type = VOID_TYPE;
  temp->nodetype = REPEAT_NODE;
  temp->left = l;
  temp->mid = NULL;
  temp->right = r;
  return temp;
}

struct tnode *makeDoWhileNode(struct tnode *l, struct tnode *r) {
  struct tnode *temp;
  temp = (struct tnode *)malloc(sizeof(struct tnode));
  temp->varname = NULL;
  temp->type = VOID_TYPE;
  temp->nodetype = DOWHILE_NODE;
  temp->left = l;
  temp->mid = NULL;
  temp->right = r;
  return temp;
}

struct tnode *makeTypeLeafNode(int var_type) {
  struct tnode *temp;
  temp = (struct tnode *)malloc(sizeof(struct tnode));
  temp->varname = NULL;
  temp->type = var_type;
  temp->nodetype = TYPE_NODE;
  temp->left = NULL;
  temp->mid = NULL;
  temp->right = NULL;
  return temp;
}

struct tnode *makeDeclNode(struct tnode *l, struct tnode *r) {
  struct tnode *temp;
  temp = (struct tnode *)malloc(sizeof(struct tnode));
  temp->varname = NULL;
  temp->type = VOID_TYPE;
  temp->nodetype = DECL_NODE;
  temp->left = l;
  temp->mid = NULL;
  temp->right = r;
  return temp;
}

struct tnode *makeStringConstantLeafNode(char *str) {
  struct tnode *temp;
  temp = (struct tnode *)malloc(sizeof(struct tnode));
  temp->varname = strdup(str);
  temp->type = STR_TYPE;
  temp->nodetype = STRCONST_NODE;
  temp->left = NULL;
  temp->mid = NULL;
  temp->right = NULL;
  return temp;
}