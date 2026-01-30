#include "symbol_table.h"
#include "../ast/ast.h"
#include "../spec/expl.h"
#include "../utility/error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VAR_SIZE 1
#define NAMEOF(x) #x

struct Gsymbol *head = NULL;
int bindingOffset = 4096;

int buildSymbolTable(struct tnode *t, int var_type) {
  if (t == NULL)
    return VOID_TYPE;

  switch (t->nodetype) {
  case CONN_NODE: {
    buildSymbolTable(t->left, var_type);
    buildSymbolTable(t->right, var_type);
    break;
  }
  case DECL_NODE: {
    int varType = buildSymbolTable(t->left, var_type);
    buildSymbolTable(t->right, varType);
    break;
  }
  case TYPE_NODE: {
    return t->type;
  }
  case VAR_NODE: {
    Install(t->varname, var_type, VAR_SIZE);
    break;
  }
  case ARR_NODE: {
    Install(t->varname, var_type, t->val * VAR_SIZE);
    break;
  }
  default: {
    report_error("Encountered Node: %s. Failed to build AST for Declaration\n",
                 nodeTypeToString(t->nodetype));
  }
  }

  return VOID_TYPE;
}

void printSymbolTable() {
  struct Gsymbol *p = head;

  printf("\n");
  printf("╔══════════════════╦══════════╦══════════╦══════════╗\n");
  printf("║ %-16s ║ %-8s ║ %-8s ║ %-8s ║\n", "Name", "Type", "Size", "Binding");
  printf("╠══════════════════╬══════════╬══════════╬══════════╣\n");

  while (p) {
    printf("║ %-16s ║ %-8s ║ %-8d ║ %-8d ║\n", p->name, typeToString(p->type),
           p->size, p->binding);
    p = p->next;
  }

  printf("╚══════════════════╩══════════╩══════════╩══════════╝\n");
  printf("\n");
}

struct Gsymbol *Lookup(char *name) {
  struct Gsymbol *p = head;

  while (p) {
    if (strcmp(p->name, name) == 0)
      return p;
    p = p->next;
  }

  return NULL;
}

void Install(char *name, int type, int size) {

  if (Lookup(name) != NULL) {
    report_error("Duplicate declaration for variable name: %s\n", name);
  }

  struct Gsymbol *temp = malloc(sizeof(struct Gsymbol));
  temp->name = name;
  temp->type = type;
  temp->size = size;
  temp->binding = bindingOffset;
  temp->next = head;
  head = temp;

  // update binding offset
  bindingOffset += size;
}