#ifndef AST_H
#define AST_H

#include <stdio.h>

#define INT_TYPE 0

#define VAR_NODE 0 // Variable - Leaf
#define OP_NODE 1 // Operator 
#define CONN_NODE 2 // Connecter
#define ASSG_NODE 3 // Assignment
#define READ_NODE 4 // Read
#define WRITE_NODE 5 // Write
#define CONST_NODE 6 // Constant - Leaf

typedef struct tnode {
  int val;       // value of a number for NUM nodes.
  int type;      // type of variable  --(Integer only for stage2)
  char *varname; // name of a variable for ID nodes
  int nodetype;  // information about non-leaf nodes - read/write/connector/+/*
                 // etc.
  struct tnode *left, *right; // left and right branches
} tnode;

struct tnode *makeConnectorNode(struct tnode *l, struct tnode *r);
struct tnode *makeAssgNode(struct tnode *l, struct tnode *r);
struct tnode *makeReadNode(struct tnode *l);
struct tnode *makeWriteNode(struct tnode *l);
struct tnode *makeVariableLeafNode(char *c);

/*Create a node tnode*/
struct tnode *createTree(int val, int type, char *c, struct tnode *l,
                         struct tnode *r);


#endif