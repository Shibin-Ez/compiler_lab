#include "ast.h"
#include <stdlib.h>
#include <string.h>

struct tnode *makeConnecterNode(struct tnode *l, struct tnode *r) {
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

struct tnode *makeVariableLeafNode(char *c) {
  struct tnode *temp;
  temp = (struct tnode *)malloc(sizeof(struct tnode));
  temp->varname = strdup(c);
  temp->type = INT_TYPE;
  temp->nodetype = VAR_NODE;
  temp->left = NULL;
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

struct tnode *makeIfElseNode(struct tnode *l, struct tnode* m, struct tnode *r) {
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