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
char fipFileContent[4096];
int currentFipFileContentSize = 0;

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

void addInFipFileContent(char* str) {
  sprintf(fipFileContent + currentFipFileContentSize, "%s ", str);
  currentFipFileContentSize += strlen(str) + 1;
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
comment "//".*$

%%

"main"        {/*"*/addInFIP(2, -1); addInFipFileContent("MAIN");}
"("           {addInFIP(3, -1); addInFipFileContent("LPAREN");}
")"           {addInFIP(4, -1); addInFipFileContent("RPAREN");}
"{"           {addInFIP(5, -1); addInFipFileContent("LBRACE");}
"}"           {addInFIP(6, -1); addInFipFileContent("RBRACE");}
";"           {addInFIP(7, -1); addInFipFileContent("SEMICOLON");}
","           {addInFIP(8, -1); addInFipFileContent("COMMA");}
"int"         {addInFIP(9, -1); addInFipFileContent("INT");}
"char"        {addInFIP(10, -1); addInFipFileContent("CHAR");}
"float"       {addInFIP(11, -1); addInFipFileContent("FLOAT");}
"double"      {addInFIP(12, -1); addInFipFileContent("DOUBLE");}
"string"      {addInFIP(13, -1); addInFipFileContent("STRING");}
"="           {addInFIP(14, -1); addInFipFileContent("ASSIGN");}
"+"           {addInFIP(15, -1); addInFipFileContent("PLUS");}
"-"           {addInFIP(16, -1); addInFipFileContent("MINUS");}
"*"           {addInFIP(17, -1); addInFipFileContent("MUL");}
"/"           {addInFIP(18, -1); addInFipFileContent("DIV");}
"%"           {addInFIP(19, -1); addInFipFileContent("MOD");}
"&"           {addInFIP(20, -1); addInFipFileContent("BIT_AND");}
"|"           {addInFIP(21, -1); addInFipFileContent("BIT_OR");}
"^"           {addInFIP(22, -1); addInFipFileContent("BIT_XOR");}
"&&"          {addInFIP(23, -1); addInFipFileContent("AND");}
"||"          {addInFIP(24, -1); addInFipFileContent("OR");}
"=="          {addInFIP(25, -1); addInFipFileContent("EQ");}
"!="          {addInFIP(26, -1); addInFipFileContent("NEQ");}
"<"           {addInFIP(27, -1); addInFipFileContent("LT");}
">"           {addInFIP(28, -1); addInFipFileContent("GT");}
"<="          {addInFIP(29, -1); addInFipFileContent("LTE");}
">="          {addInFIP(30, -1); addInFipFileContent("GTE");}
"<<"          {addInFIP(31, -1); addInFipFileContent("LSHIFT");}
">>"          {addInFIP(32, -1); addInFipFileContent("RSHIFT");}
"!"           {addInFIP(33, -1); addInFipFileContent("NOT");}
"if"          {addInFIP(34, -1); addInFipFileContent("IF");}
"else"        {addInFIP(35, -1); addInFipFileContent("ELSE");}
"while"       {addInFIP(36, -1); addInFipFileContent("WHILE");}
"for"         {addInFIP(37, -1); addInFipFileContent("FOR");}
"struct"      {addInFIP(38, -1); addInFipFileContent("STRUCT");}
"."           {addInFIP(39, -1); addInFipFileContent("DOT");}
"cin"         {addInFIP(40, -1); addInFipFileContent("CIN");}
"cout"        {addInFIP(41, -1); addInFipFileContent("COUT");}
"switch"      {addInFIP(42, -1); addInFipFileContent("SWITCH");}
"case"        {addInFIP(43, -1); addInFipFileContent("CASE");}
"default"     {addInFIP(44, -1); addInFipFileContent("DEFAULT");}
":"           {addInFIP(45, -1); addInFipFileContent("COLON");}
"break"       {addInFIP(46, -1); addInFipFileContent("BREAK");}

{number}|{string}|{char}        {addCustom(yytext, 1); addInFipFileContent("CONST");}
{identifier}                    {addCustom(yytext, 0); addInFipFileContent("IDENTIFIER");}
{comment}                       {addInFipFileContent("COMMENT");}
[\n]                            {currentLine++;}
[ \n\t]                         {;}
.                               {errorsFound++; printf("Unknown token at line %d: %s\n", currentLine, yytext);}

%%

int main(int argc, char* argv[]) {
  if (argc != 3) {
    printf("Invalid syntax!\nUsage: %s <input file name> <output file name>\n", argv[0]);
    exit(1);
  }
  char input_file[256], output_file[256];
  sprintf(input_file, "../files/raw/%s", argv[1]);
  sprintf(output_file, "../files/fip/%s", argv[2]);
  FILE* fin = fopen(input_file, "r");
  FILE* fout = fopen(output_file, "w");
  TS.tree = initTree();
  FIP = (FipElem*)malloc(500 * sizeof(FipElem));
  initIdentifierAndConsts();

  // yyin - a pointer to the input file
  yyin = fin;

  yyrestart(yyin);

  // yylex - the main flex function
  yylex();

  if (errorsFound == 0) {
    TS.data = dataInorder(TS.tree);
    assignTsDataToFIP();
    printTS();
    printFIP();
    fipFileContent[strlen(fipFileContent) - 1] = '\0';
    fprintf(fout, "%s", fipFileContent);
  }

  fclose(fin);
  fclose(fout);
  destroyTree(TS.tree);
  free(FIP);
  deleteCustom();

  return 0;
}