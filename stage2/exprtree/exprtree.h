#ifndef EXPRTREE_H
#define EXPRTREE_H

#include <stdio.h>

/*Make a leaf tnode and set the value of val field*/
struct tnode *makeConstantLeafNode(int n);

/*Make a tnode with opertor, left and right branches set*/
struct tnode *makeOperatorNode(char c, struct tnode *l, struct tnode *r);

#endif /* EXPRTREE_H */