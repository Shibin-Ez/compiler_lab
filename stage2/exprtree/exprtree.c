#include "exprtree.h"
#include "../ast/ast.h"
#include <stdlib.h>

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

struct tnode *makeOperatorNode(char c, struct tnode *l, struct tnode *r) {
  struct tnode *temp;
  temp = (struct tnode *)malloc(sizeof(struct tnode));
  temp->varname = malloc(sizeof(char));
  *(temp->varname) = c;
  temp->nodetype = OP_NODE;
  temp->left = l;
  temp->right = r;
  return temp;
}