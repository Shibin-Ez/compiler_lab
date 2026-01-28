#include "exprtree.h"
#include "../ast/ast.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tnode *makeConstantLeafNode(int n) {
  struct tnode *temp;
  temp = (struct tnode *)malloc(sizeof(struct tnode));
  temp->varname = NULL;
  temp->val = n;
  temp->type = INT_TYPE;
  temp->nodetype = CONST_NODE;
  temp->left = NULL;
  temp->right = NULL;
  return temp;
}

struct tnode *makeOperatorNode(char *op, struct tnode *l, struct tnode *r) {
  assert(l && r);

  struct tnode *temp;
  temp = (struct tnode *)malloc(sizeof(struct tnode));

  // Type checking
  char firstChar = op[0];
  if (firstChar == '+' || firstChar == '-' || firstChar == '*' ||
      firstChar == '/') {
    // Type of both must be integer
    if (l->type == INT_TYPE && r->type == INT_TYPE) {

      temp->type = INT_TYPE;

    } else {
      printf("Type Mismatch!!!\n");
      printf("Expected Integer Type\n");
      exit(1);
    }
  } else {
    // Type of both must be Bool
    if (l->type == INT_TYPE && r->type == INT_TYPE) {
      temp->type = BOOL_TYPE;
    } else {
      printf("Type Mismatch!!!\n");
      printf("Expected Integer Type\n");
      exit(1);
    }
  }

  temp->varname = strdup(op);
  temp->nodetype = OP_NODE;
  temp->left = l;
  temp->right = r;
  return temp;
}