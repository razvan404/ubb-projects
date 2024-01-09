%{

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

TableOfSymbols TS;
FipElem* FIP;
int fipSize = 0;

int currentLine = 1;
int errorsFound = 0;

void addInFIP(int atomCode, int tsPosition) {
  FIP[fipSize].atomCode = atomCode;
  FIP[fipSize++].tsPosition = tsPosition;
}

void printTS() {
  printf("==================\n");
  printf("Table of Symbols\n");
  printf("Code\tAtom\n");
  for (int i = 0; i < TS.tree->size; i++) {
    printf("%d\t%s\n", i, TS.data[i]);
  }
  printf("==================\n");
}

void printFIP() {
  printf("==================\n");
  printf("FIP\n");
  printf("Code\tTS Position\n");
  for (int i = 0; i < fipSize; i++) {
    if (FIP[i].tsPosition == -1) {
      printf("%d\t(nil)\n", FIP[i].atomCode);
    } else {
      printf("%d\t%d\n", FIP[i].atomCode, FIP[i].tsPosition);
    }
  }
  printf("==================\n");
}

char** custom;
int sizeCustom;

void initIdentifierAndConsts() {
  custom = (char**)malloc(500 * sizeof(char*));
  sizeCustom = 0;
}

void addCustom(char* elem, int isConst) {
  char* elemCpy = (char*)malloc(sizeof(char) * (strlen(elem) + 1));
  strcpy(elemCpy, elem);
  custom[sizeCustom++] = elemCpy;
  addInFIP(isConst, -2);
  insertIfDoesntExist(TS.tree, elemCpy);
}

void deleteCustom() {
  for (int i = 0; i < sizeCustom; i++) {
    free(custom[i]);
  }
  sizeCustom = 0;
  free(custom);
}

int binarySearchTsData(char* elem) {
  int left = 0;
  int right = TS.tree->size - 1;
  while (left <= right) {
    int mid = (left + right) / 2;
    int cmp = strcmp(elem, TS.data[mid]);
    if (cmp == 0) {
      return mid;
    } else if (cmp < 0) {
      right = mid - 1;
    } else {
      left = mid + 1;
    }
  }
  return -3;
}

void assignTsDataToFIP() {
  int elemsSoFar = 0;
  for (int i = 0; i < fipSize; i++) {
    if (FIP[i].atomCode == 0 || FIP[i].atomCode == 1) {
      int tsPosition = binarySearchTsData(custom[elemsSoFar]);
      FIP[i].tsPosition = tsPosition;
      elemsSoFar++;
    }
  }
}

%}

%option noyywrap

digit [0-9]
nzdigit [1-9]
letter [a-zA-Z_]
number ([+-]?({nzdigit}{digit}*)|"0")("."{digit}+)?
string \"[^\"\n]*\"     
char \'\\?.\'           
identifier {letter}({letter}|{digit}){0,249}

%%

"main"        {/*"*/addInFIP(2, -1);}
"("           {addInFIP(3, -1);}
")"           {addInFIP(4, -1);}
"{"           {addInFIP(5, -1);}
"}"           {addInFIP(6, -1);}
";"           {addInFIP(7, -1);}
","           {addInFIP(8, -1);}
"int"         {addInFIP(9, -1);}
"char"        {addInFIP(10, -1);}
"float"       {addInFIP(11, -1);}
"double"      {addInFIP(12, -1);}
"string"      {addInFIP(13, -1);}
"="           {addInFIP(14, -1);}
"+"           {addInFIP(15, -1);}
"-"           {addInFIP(16, -1);}
"*"           {addInFIP(17, -1);}
"/"           {addInFIP(18, -1);}
"%"           {addInFIP(19, -1);}
"&"           {addInFIP(20, -1);}
"|"           {addInFIP(21, -1);}
"^"           {addInFIP(22, -1);}
"&&"          {addInFIP(23, -1);}
"||"          {addInFIP(24, -1);}
"=="          {addInFIP(25, -1);}
"!="          {addInFIP(26, -1);}
"<"           {addInFIP(27, -1);}
">"           {addInFIP(28, -1);}
"<="          {addInFIP(29, -1);}
">="          {addInFIP(30, -1);}
"<<"          {addInFIP(31, -1);}
">>"          {addInFIP(32, -1);}
"if"          {addInFIP(33, -1);}
"else"        {addInFIP(34, -1);}
"while"       {addInFIP(35, -1);}
"for"         {addInFIP(36, -1);}
"struct"      {addInFIP(37, -1);}
"."           {addInFIP(38, -1);}
"cin"         {addInFIP(39, -1);}
"cout"        {addInFIP(40, -1);}
"switch"      {addInFIP(41, -1);}
"case"        {addInFIP(42, -1);}
"default"     {addInFIP(43, -1);}
":"           {addInFIP(44, -1);}
"break"       {addInFIP(45, -1);}

{number}|{string}|{char}        {addCustom(yytext, 1);}
{identifier}                    {addCustom(yytext, 0);}
[\n]                            {currentLine++;}
[ \n\t]                         {;}
.                               {errorsFound++; printf("Unknown token at line %d: %s\n", currentLine, yytext);}

%%

int main(int argc, char* argv[]) {
  if (argc != 2) {
    printf("Invalid syntax!\nUsage: %s <file name>\n", argv[0]);
    exit(1);
  }
  FILE* fp = fopen(argv[1], "r");
  TS.tree = initTree();
  FIP = (FipElem*)malloc(500 * sizeof(FipElem));
  initIdentifierAndConsts();

  // yyin - a pointer to the input file
  yyin = fp;

  yyrestart(yyin);

  // yylex - the main flex function
  yylex();

  if (errorsFound == 0) {
    TS.data = dataInorder(TS.tree);
    assignTsDataToFIP();
    printTS();
    printFIP();
  }

  fclose(fp);
  destroyTree(TS.tree);
  free(FIP);
  deleteCustom();

  return 0;
}