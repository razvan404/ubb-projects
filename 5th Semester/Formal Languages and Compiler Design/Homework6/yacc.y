%{
    #include <stdio.h>
    #include <string.h>
    #include <stdint.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include "flex.h"

    extern int yylex();
    extern char* yytext;
    extern FILE* yyin;

    void yyerror(const char* str);

    char dataSegment[5000];
    int dataSegmentLen = 0;

    char code[20000];

    void updateDataSegmentLen() {
        dataSegmentLen += strlen(dataSegment + dataSegmentLen);
    }

    void reserveTypeInDataSegment(char* varname, char* type, int size) {
        sprintf(dataSegment + dataSegmentLen, "\t%s\t\t%s\t\t%d\n", varname, type, size);
        updateDataSegmentLen();
    }

    char *multiTok(char *input, char *delimiter) {
        static char *string;
        if (input != NULL)
            string = input;

        if (string == NULL)
            return string;

        char *end = strstr(string, delimiter);
        if (end == NULL) {
            char *temp = string;
            string = NULL;
            return temp;
        }

        char *temp = string;

        *end = '\0';
        string = end + strlen(delimiter);
        return temp;
    }
    
    int stringsDefined = 0;
    int defineStringInDataSegment(char* value) {
        sprintf(dataSegment + dataSegmentLen, "\tstr%d\tDB\t\t", ++stringsDefined);
        updateDataSegmentLen();
        char *prev = multiTok(value, "\\n");
        char *next = multiTok(NULL, "\\n");
        while (next != NULL) {
            if (strlen(prev) > 0) {
                sprintf(dataSegment + dataSegmentLen, "'%s', 10, ", prev);
            } else {
                sprintf(dataSegment + dataSegmentLen, "10, ");
            }
            updateDataSegmentLen();
            prev = next;
            next = multiTok(NULL, "\\n");
        }
        if (strlen(prev) > 0) {
            sprintf(dataSegment + dataSegmentLen, "'%s', 0\n", prev);
        } else {
            sprintf(dataSegment + dataSegmentLen, "0\n");
        }
        updateDataSegmentLen();
        return stringsDefined;
    }

    char tempArray[] = "tmp";
    int tempVarsLen = 0;
    int newTempVar() {
        return tempVarsLen++;
    }

    void defineDefaults() {
        reserveTypeInDataSegment(tempArray, "RESD", tempVarsLen);
    }

    struct ioStatement {
        int currentLen;
        char currentFormat[1000];    
    } inputStatement, outputStatement;

    void resetIoStatement(struct ioStatement* stmt) {
        stmt->currentLen = 0;
        strcpy(stmt->currentFormat, "");
    }

    void setDefaults() {
        resetIoStatement(&inputStatement);
        resetIoStatement(&outputStatement);
    }
%}

%union {
    struct {
        char varname[1000];
        char code[1000];
    } varnameAndCode;
    char varname[1000];
    char code[1000];
}

%token MAIN LPAREN RPAREN LBRACE RBRACE INT
%token SEMICOLON ADD SUB MUL DIV
%token CIN RSHIFT COUT LSHIFT
%token COMMA ASSIGN
%token<varname> IDENTIFIER INTEGER STRING

%type<code> main_function instructions instruction normal_instruction

%type<code> declaration
%type<varnameAndCode> declaration_sequence declaration_term
%type<varname> declaration_type

%type<varnameAndCode> assignment expression expression_factor expression_term

%type<code> input_statement input_sequence output_statement output_sequence
%type<varnameAndCode> output_term

%%

program: main_function {
        sprintf(
            code,
            "bits 32\nglobal start\n\n"
            "extern exit\nimport exit msvcrt.dll\n"
            "extern scanf\nimport scanf msvcrt.dll\n"
            "extern printf\nimport printf msvcrt.dll\n\n"
            "segment data use32 class=data\n%s\n"
            "segment data use32 class=code\n%s\n",
            dataSegment, $1
        );
    }
main_function: INT MAIN LPAREN RPAREN LBRACE instructions RBRACE {
        defineDefaults();
        sprintf(
            $$,
            "\tstart:\n%s\n"
            "\t;exit\n\t\tPUSH\t\tDWORD\t\t0\n"
            "\t\tCALL\t\t[exit]",
            $6
        );
    }

instructions: instruction instructions {
        sprintf($$, "%s\n%s", $1, $2);
    }
    | instruction {
        strcpy($$, $1);
    }
instruction: normal_instruction SEMICOLON {
        strcpy($$, $1);
    }
normal_instruction: declaration {
        strcpy($$, $1);
    }
    | assignment {
        strcpy($$, $1.code);
    }
    | input_statement {
        strcpy($$, $1);
    }
    | output_statement {
        strcpy($$, $1);
    }

declaration: declaration_type declaration_sequence {    
    char* p = strtok($2.varname, " ");
    char* type = $1;
    while (p != NULL) {
        reserveTypeInDataSegment(p, type, 1);
        p = strtok(NULL, " ");
    }
    strcpy($$, $2.code);
}
declaration_sequence: declaration_term COMMA declaration_sequence {
        sprintf($$.varname, "%s %s", $1.varname, $3.varname);
        sprintf($$.code, "%s\n%s", $1.code, $3.code);
    }
    | declaration_term {
        strcpy($$.varname, $1.varname);
        strcpy($$.code, $1.code);
    }
declaration_term: IDENTIFIER {
        strcpy($$.varname, $1);
        strcpy($$.code, "");
    }
    | assignment;

declaration_type: INT {
    strcpy($$, "RESD");
}

assignment: IDENTIFIER ASSIGN expression {
    strcpy($$.varname, $1);
    sprintf(
        $$.code,
        "%s\t; %s = %s\n"
        "\t\tMOV\t\tEAX,\t\t%s\n\t\tMOV\t\t[%s],\t\tEAX\n",
        $3.code, $1, $3.varname, $3.varname, $1
    );
}

expression: expression_factor {
        strcpy($$.varname, $1.varname);
        strcpy($$.code, $1.code);
    }
    | expression ADD expression_factor {
        int tempVarIdx = newTempVar();
        sprintf($$.varname, "[%s + %d]", tempArray, 4 * tempVarIdx);
        sprintf(
            $$.code,
            "%s%s\t; %s = %s + %s\n"
            "\t\tMOV\t\tEAX,\t\t%s\n"
            "\t\tADD\t\tEAX,\t\t%s\n"
            "\t\tMOV\t\t%s,\t\tEAX\n",
            $1.code, $3.code, $$.varname, $1.varname, $3.varname,
            $1.varname, $3.varname, $$.varname
        );
    }
    | expression SUB expression_factor {
        int tempVarIdx = newTempVar();
        sprintf($$.varname, "[%s + %d]", tempArray, 4 * tempVarIdx);
        sprintf(
            $$.code,
            "%s%s\t; %s = %s - %s\n"
            "\t\tMOV\t\tEAX,\t\t%s\n"
            "\t\tSUB\t\tEAX,\t\t%s\n"
            "\t\tMOV\t\t%s,\t\tEAX\n",
            $1.code, $3.code, $$.varname, $1.varname, $3.varname,
            $1.varname, $3.varname, $$.varname
        );
    }

expression_factor: expression_term {
        strcpy($$.varname, $1.varname);
        strcpy($$.code, $1.code);
    }
    | expression_factor MUL expression_term {
        int tempVarIdx = newTempVar();
        sprintf($$.varname, "[%s + %d]", tempArray, 4 * tempVarIdx);
        sprintf(
            $$.code,
            "%s%s\t; %s = %s * %s\n"
            "\t\tMOV\t\tEBX,\t\t%s\n"
            "\t\tMOV\t\tEAX,\t\t%s\n"
            "\t\tIMUL\tEBX\n"
            "\t\tMOV\t\t%s,\t\tEAX\n",
            $1.code, $3.code, $$.varname, $1.varname, $3.varname,
            $1.varname, $3.varname, $$.varname
        );
    }
    | expression_factor DIV expression_term {
        int tempVarIdx = newTempVar();
        sprintf($$.varname, "[%s + %d]", tempArray, 4 * tempVarIdx);
        sprintf(
            $$.code,
            "%s%s\t; %s = %s / %s\n"
            "\t\tMOV\t\tEDX,\t\t0\n"
            "\t\tMOV\t\tEAX,\t\t%s\n"
            "\t\tMOV\t\tEBX,\t\t%s\n"
            "\t\tIDIV\tEBX\n"
            "\t\tMOV\t\t%s,\t\tEAX\n",
            $1.code, $3.code, $$.varname, $1.varname, $3.varname,
            $1.varname, $3.varname, $$.varname
        );
    }

expression_term: INTEGER {
        strcpy($$.varname, $1);
        strcpy($$.code, "");
    }
    | IDENTIFIER {
        sprintf($$.varname, "[%s]", $1);
        strcpy($$.code, "");
    }
    | LPAREN expression RPAREN {
        strcpy($$.varname, $2.varname);
        strcpy($$.code, $2.code);
    }

input_statement: CIN RSHIFT input_sequence {
        int stringIdx = defineStringInDataSegment(inputStatement.currentFormat);
        sprintf(
            $$,
            "\t; input statement\n%s"
            "\t\tPUSH\tDWORD\t\tstr%d\n"
            "\t\tCALL\t[scanf]\n"
            "\t\tADD\t\tESP,\t\t4 * %d\n",
            $3, stringIdx, inputStatement.currentLen + 1
        );
        resetIoStatement(&inputStatement);
    }
input_sequence: IDENTIFIER RSHIFT input_sequence {
        sprintf($$, "%s\t\tPUSH\tDWORD\t\t%s\n", $3, $1);
        ++inputStatement.currentLen;
        sprintf(inputStatement.currentFormat, "%s%%%%d", inputStatement.currentFormat);
    }
    | IDENTIFIER {
        sprintf($$, "\t\tPUSH\tDWORD\t\t%s\n", $1);
        ++inputStatement.currentLen;
        strcpy(inputStatement.currentFormat, "%%d");
    }

output_statement: COUT LSHIFT output_sequence {
        int stringIdx = defineStringInDataSegment(outputStatement.currentFormat);
        sprintf(
            $$,
            "\t; output statement\n%s"
            "\t\tPUSH\tDWORD\t\tstr%d\n"
            "\t\tCALL\t[printf]\n"
            "\t\tADD\t\tESP,\t\t4 * %d\n",
            $3, stringIdx, outputStatement.currentLen + 1
        );
        resetIoStatement(&outputStatement);
    }
output_sequence: output_term LSHIFT output_sequence {
        if (strcmp($1.varname, "") != 0) {
            sprintf($$, "%s%s\t\tPUSH\tDWORD\t\t%s\n", $3, $1.code, $1.varname);
            ++outputStatement.currentLen;
        } else {
            strcpy($$, $3);
        }
    }
    | output_term {
        if (strcmp($1.varname, "") != 0) {
            sprintf($$, "%s\t\tPUSH\tDWORD\t\t%s\n", $1.code, $1.varname);
            ++outputStatement.currentLen;
        }
    }
output_term: STRING {
        $1[strlen($1) - 1] = '\0';
        sprintf(outputStatement.currentFormat, "%s%s", outputStatement.currentFormat, $1 + 1);
        strcpy($$.varname, "");
        strcpy($$.code, "");
    }
    | expression {
        sprintf(outputStatement.currentFormat, "%s%%%%d", outputStatement.currentFormat);
        sprintf($$.varname, "%s", $1.varname);
        strcpy($$.code, $1.code);
    }

%%

void yyerror(const char* str) {
    fprintf(stderr, "Syntax error on line %d: %s\n", getCurrentLine(), str);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Invalid syntax!\nUsage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }
    setDefaults();
    char file[256];
    sprintf(file, "files/%s", argv[1]);
    yyin = fopen(file, "r");
    if (yyin == NULL) {
        printf("File not found!\n");
        exit(1);
    }

    yyparse();
    fclose(yyin);
    int errorsFound = getErrorsFound();
    if (errorsFound != 0) {
        fprintf(stderr, "There are %d lexical errors in your program!\n", errorsFound);
        exit(1);
    }

    sprintf(file, "files/%s", argv[2]);
    FILE* fout = fopen(file, "w");
    fprintf(fout, code);
    fclose(fout);

    return 0;
}