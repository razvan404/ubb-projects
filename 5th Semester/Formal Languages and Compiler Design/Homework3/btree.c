#include "btree.h"

Tree* initTree() {
  Tree* tree = (Tree*)malloc(sizeof(Tree));
  tree->root = NULL;
  tree->size = 0;
  return tree;
}

int containsRecursive(Node* root, char* data) {
  if (root == NULL) {
    return 0;
  } else {
    int cmp = strcmp(data, root->data);
    if (cmp == 0) {
      return 1;
    } else if (cmp < 0) {
      return containsRecursive(root->left, data);
    } else {
      return containsRecursive(root->right, data);
    }
  }
}

int contains(Tree* tree, char* data) {
  return containsRecursive(tree->root, data);
}

Node* insertIfDoesntExistRecursive(Node* root, char* data, int* size) {
  if (root == NULL) {
    root = (Node*)malloc(sizeof(Node));
    root->data = data;
    root->left = NULL;
    root->right = NULL;
    (*size)++;
  } else {
    int cmp = strcmp(data, root->data);
    if (cmp == 0) {
      return root;
    } else if (cmp < 0) {
      root->left = insertIfDoesntExistRecursive(root->left, data, size);
    } else {
      root->right = insertIfDoesntExistRecursive(root->right, data, size);
    }
  }
  return root;
}

void insertIfDoesntExist(Tree* tree, char* data) {
  tree->root = insertIfDoesntExistRecursive(tree->root, data, &tree->size);
}

void dataInorderRecursive(Node* root, char** data, int* i) {
  if (root != NULL) {
    dataInorderRecursive(root->left, data, i);
    data[*i] = root->data;
    (*i)++;
    dataInorderRecursive(root->right, data, i);
  }
}

char** dataInorder(Tree* tree) {
  char** data = (char**)malloc(sizeof(char*) * tree->size);
  int i = 0;
  dataInorderRecursive(tree->root, data, &i);
  return data;
}

void destroyRecursive(Node* root) {
  if (root != NULL) {
    destroyRecursive(root->left);
    destroyRecursive(root->right);
    free(root);
  }
}

void destroyTree(Tree* tree) {
  destroyRecursive(tree->root);
  free(tree);
}