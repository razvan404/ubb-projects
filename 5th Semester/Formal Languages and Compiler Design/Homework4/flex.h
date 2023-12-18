// flex.h
#ifndef FLEX_H
#define FLEX_H

#include <stdio.h>
#include "btree.h"

typedef struct {
  Tree* tree;
  char** data;
} TableOfSymbols;

typedef struct {
  int atomCode;
  int tsPosition;
} FipElem;

void printTS();
void printFIP();
void assignTsDataToFIP();

void initFlexResources();
void destroyFlexResources();

int getCurrentLine();
int getErrorsFound();

#endif