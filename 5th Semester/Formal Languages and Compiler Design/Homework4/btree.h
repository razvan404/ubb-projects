#ifndef BTREE_H
#define BTREE_H

#include <stdlib.h>
#include <string.h>

typedef struct Node {
  char* data;
  struct Node* left;
  struct Node* right;
} Node;

typedef struct {
  Node* root;
  int size;
} Tree;

Tree* initTree();
int contains(Tree* tree, char* data);
void insertIfDoesntExist(Tree* tree, char* data);
char** dataInorder(Tree* tree);
void destroyTree(Tree* tree);

#endif