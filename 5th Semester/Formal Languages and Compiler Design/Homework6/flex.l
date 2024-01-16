%{
#include <string.h>
#include "flex.h"
#include "yacc.tab.h"

int currentLine = 1;
int errorsFound = 0;

int getCurrentLine() {
    return currentLine;
}

int getErrorsFound() {
    return errorsFound;
}

%}

%option noyywrap

digit [0-9]
nzdigit [1-9]
letter [a-zA-Z_]
integer [+-]?({nzdigit}{digit}*)|"0"
real ([+-]?({nzdigit}{digit}*)|"0")("."{digit}+)?
string \"[^\"\n]*\"     
char \'\\?.\'           
identifier {letter}({letter}|{digit}){0,249}
comment "//".*$

%%

"main"        {return MAIN;}
"("           {return LPAREN;}
")"           {return RPAREN;}
"{"           {return LBRACE;}
"}"           {return RBRACE;}
";"           {return SEMICOLON;}
","           {return COMMA;}
"int"         {return INT;}
"="           {return ASSIGN;}
"+"           {return ADD;}
"-"           {return SUB;}
"*"           {return MUL;}
"/"           {return DIV;}
"<<"          {return LSHIFT;}
">>"          {return RSHIFT;}
"cin"         {return CIN;}
"cout"        {return COUT;}

{integer}                       {strcpy(yylval.varname, yytext); return INTEGER;}
{string}                        {strcpy(yylval.varname, yytext); return STRING;}
{identifier}                    {strcpy(yylval.varname, yytext); return IDENTIFIER;}
[\n]                            {currentLine++;}
[ \n\t]                         {;}
.                               {errorsFound++; printf("Unknown token at line %d: %s\n", currentLine, yytext);}

%%