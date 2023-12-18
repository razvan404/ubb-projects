%{
  #include "flex.h"

  extern int yylex();
  extern FILE* yyin;

  void yyerror(const char* str);
%}

%token MAIN LPAREN RPAREN LBRACE RBRACE SEMICOLON COMMA
%token INT CHAR FLOAT DOUBLE STRING
%token ASSIGN PLUS MINUS MUL DIV MOD
%token BIT_AND BIT_OR BIT_XOR
%token LSHIFT RSHIFT NOT
%token AND OR EQ NEQ LT GT LTE GTE
%token IF ELSE WHILE FOR
%token STRUCT DOT
%token CIN COUT SWITCH CASE DEFAULT BREAK COLON
%token CONST IDENTIFIER
%token COMMENT UNKNOWN

%%

program: global_blocks main_function global_blocks;
global_blocks: global_block global_blocks
  | eps;
global_block: struct_definition
  | COMMENT;
main_function: INT MAIN LPAREN RPAREN LBRACE instructions RBRACE;

instructions: instruction SEMICOLON instructions
  | special_instruction instructions
  | COMMENT instructions
  | eps;
instruction: declaration
  | operation
  | expression
  | input_statement
  | output_statement;
special_instruction: conditional_statement
  | loop_statement
  | struct_definition;

declaration: type declaration_sequence;
declaration_sequence: declaration_term
  | declaration_term COMMA declaration_sequence;
declaration_term: IDENTIFIER
  | assignment;

type: INT
  | CHAR
  | FLOAT
  | DOUBLE
  | STRING
  | STRUCT IDENTIFIER;

assignment: accesible_term ASSIGN expression;
operation: assignment
  | accesible_term mathematical_operator ASSIGN expression;

accesible_term: IDENTIFIER
  | IDENTIFIER DOT accesible_term;

struct_definition: STRUCT IDENTIFIER LBRACE struct_members RBRACE optional_declaration_sequence SEMICOLON;
optional_declaration_sequence: declaration_sequence
  | eps;
struct_members: declaration SEMICOLON
  | declaration SEMICOLON struct_members;

expression: expression_term
  | expression_term mathematical_operator expression;
expression_term: accesible_term
  | CONST;

mathematical_operator: arithmetic_operator
  | bitwise_operator;
arithmetic_operator: PLUS
  | MINUS
  | MUL
  | DIV
  | MOD;
bitwise_operator: BIT_AND
  | BIT_OR
  | BIT_XOR;
logical_operator: AND
  | OR;
relational_operator: EQ
  | NEQ
  | LT
  | GT
  | LTE
  | GTE;

input_statement: CIN RSHIFT input_sequence;
input_sequence: accesible_term
  | accesible_term RSHIFT input_sequence;

output_statement: COUT LSHIFT output_sequence;
output_sequence: expression
  | expression LSHIFT output_sequence;

conditional_statement: if_statement
  | switch_statement;
if_statement: IF LPAREN conditions RPAREN LBRACE instructions RBRACE
  | IF LPAREN conditions RPAREN LBRACE instructions RBRACE ELSE LBRACE instructions RBRACE;
conditions: condition
  | condition logical_operator conditions;
condition: expression relational_operator expression
  | NOT LPAREN condition RPAREN;

loop_statement: while_loop
  | for_loop;
while_loop: WHILE LPAREN conditions RPAREN LBRACE instructions RBRACE;
for_loop: FOR LPAREN declaration SEMICOLON conditions SEMICOLON operation RPAREN LBRACE instructions RBRACE;

switch_statement: SWITCH LPAREN expression RPAREN LBRACE case_instructions default_instruction RBRACE ;
case_instructions: case_instruction case_instructions
  | case_instruction;
case_instruction: CASE CONST COLON instructions BREAK SEMICOLON;
default_instruction: DEFAULT COLON instructions BREAK SEMICOLON;

eps: %empty;

%%

void yyerror(const char* str) {
  fprintf(stderr, "Syntax error on line %d: %s\n", getCurrentLine(), str);
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    printf("Invalid syntax!\nUsage: %s <file name>\n", argv[0]);
    exit(1);
  }
  FILE* fp = fopen(argv[1], "r");
  if (fp == NULL) {
    printf("File not found!\n");
    exit(1);
  }
  initFlexResources();

  yyin = fp;
  yyparse();
  if (1) {
    printf("Program good...\n");
    assignTsDataToFIP();
    printTS();
    printFIP();
  } else {
    printf("Program bad...\n");
  }

  fclose(fp);
  destroyFlexResources();
  return 0;
}