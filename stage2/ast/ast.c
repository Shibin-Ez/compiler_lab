#include "ast.h"
#include <stdlib.h>
#include <string.h>

struct tnode *makeConnectorNode(struct tnode *l, struct tnode *r) {
  struct tnode *temp;
  temp = (struct tnode *)malloc(sizeof(struct tnode));
  temp->varname = NULL;
  temp->nodetype = CONN_NODE;
  temp->left = l;
  temp->right = r;
  return temp;
}

struct tnode *makeAssgNode(struct tnode *l, struct tnode *r) {
  struct tnode *temp;
  temp = (struct tnode *)malloc(sizeof(struct tnode));
  temp->varname = NULL;
  temp->nodetype = ASSG_NODE;
  temp->left = l;
  temp->right = r;
  return temp;
}

struct tnode *makeReadNode(struct tnode *l) {
  struct tnode *temp;
  temp = (struct tnode *)malloc(sizeof(struct tnode));
  temp->varname = NULL;
  temp->nodetype = READ_NODE;
  temp->left = l;
  temp->right = NULL;
  return temp;
}

struct tnode *makeWriteNode(struct tnode *l) {
  struct tnode *temp;
  temp = (struct tnode *)malloc(sizeof(struct tnode));
  temp->varname = NULL;
  temp->nodetype = WRITE_NODE;
  temp->left = l;
  temp->right = NULL;
  return temp;
}

struct tnode *makeVariableLeafNode(char *c) {
  struct tnode *temp;
  temp = (struct tnode *)malloc(sizeof(struct tnode));
  temp->varname = strdup(c);
  temp->nodetype = VAR_NODE;
  temp->left = NULL;
  temp->right = NULL;
  return temp;  
}