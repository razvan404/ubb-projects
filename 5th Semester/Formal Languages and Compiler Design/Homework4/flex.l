%{
#include "btree.h"
#include "flex.h"
#include "yacc.tab.h"

TableOfSymbols TS;
FipElem* FIP;
int fipSize = 0;

int currentLine = 1;
int errorsFound = 0;

int getCurrentLine() {
  return currentLine;
}

int getErrorsFound() {
  return errorsFound;
}

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
  TS.data = dataInorder(TS.tree);
  int elemsSoFar = 0;
  for (int i = 0; i < fipSize; i++) {
    if (FIP[i].atomCode == 0 || FIP[i].atomCode == 1) {
      int tsPosition = binarySearchTsData(custom[elemsSoFar]);
      FIP[i].tsPosition = tsPosition;
      elemsSoFar++;
    }
  }
}

void initFlexResources() {
  TS.tree = initTree();
  FIP = (FipElem*)malloc(500 * sizeof(FipElem));
  initIdentifierAndConsts();
}

void destroyFlexResources() {
  destroyTree(TS.tree);
  free(FIP);
  deleteCustom();
}

%}

%option noyywrap

digit [0-9]
nzdigit [1-9]
letter [a-zA-Z_]
number [+-]?({nzdigit}{digit}*)|"0"(\.{digit}+)?
string \"[^\"\n]*\"     
char \'\\?.\'           
identifier {letter}({letter}|{digit}){0,249}
comment "//".*$

%%

"main"        {/*"*/addInFIP(2, -1); return MAIN;}
"("           {addInFIP(3, -1); return LPAREN;}
")"           {addInFIP(4, -1); return RPAREN;}
"{"           {addInFIP(5, -1); return LBRACE;}
"}"           {addInFIP(6, -1); return RBRACE;}
";"           {addInFIP(7, -1); return SEMICOLON;}
","           {addInFIP(8, -1); return COMMA;}
"int"         {addInFIP(9, -1); return INT;}
"char"        {addInFIP(10, -1); return CHAR;}
"float"       {addInFIP(11, -1); return FLOAT;}
"double"      {addInFIP(12, -1); return DOUBLE;}
"string"      {addInFIP(13, -1); return STRING;}
"="           {addInFIP(14, -1); return ASSIGN;}
"+"           {addInFIP(15, -1); return PLUS;}
"-"           {addInFIP(16, -1); return MINUS;}
"*"           {addInFIP(17, -1); return MUL;}
"/"           {addInFIP(18, -1); return DIV;}
"%"           {addInFIP(19, -1); return MOD;}
"&"           {addInFIP(20, -1); return BIT_AND;}
"|"           {addInFIP(21, -1); return BIT_OR;}
"^"           {addInFIP(22, -1); return BIT_XOR;}
"&&"          {addInFIP(23, -1); return AND;}
"||"          {addInFIP(24, -1); return OR;}
"=="          {addInFIP(25, -1); return EQ;}
"!="          {addInFIP(26, -1); return NEQ;}
"<"           {addInFIP(27, -1); return LT;}
">"           {addInFIP(28, -1); return GT;}
"<="          {addInFIP(29, -1); return LTE;}
">="          {addInFIP(30, -1); return GTE;}
"<<"          {addInFIP(31, -1); return LSHIFT;}
">>"          {addInFIP(32, -1); return RSHIFT;}
"!"           {addInFIP(33, -1); return NOT;}
"if"          {addInFIP(34, -1); return IF;}
"else"        {addInFIP(35, -1); return ELSE;}
"while"       {addInFIP(36, -1); return WHILE;}
"for"         {addInFIP(37, -1); return FOR;}
"struct"      {addInFIP(38, -1); return STRUCT;}
"."           {addInFIP(39, -1); return DOT;}
"cin"         {addInFIP(40, -1); return CIN;}
"cout"        {addInFIP(41, -1); return COUT;}
"switch"      {addInFIP(42, -1); return SWITCH;}
"case"        {addInFIP(43, -1); return CASE;}
"default"     {addInFIP(44, -1); return DEFAULT;}
":"           {addInFIP(45, -1); return COLON;}
"break"       {addInFIP(46, -1); return BREAK;}

{number}|{string}|{char}        {addCustom(yytext, 1); return CONST;}
{identifier}                    {addCustom(yytext, 0); return IDENTIFIER;}
{comment}                       {return COMMENT;}
[\n]                            {currentLine++;}
[ \n\t]                         {;}
.                               {errorsFound++; printf("Unknown token at line %d: %s\n", currentLine, yytext); return UNKNOWN;}

%%
