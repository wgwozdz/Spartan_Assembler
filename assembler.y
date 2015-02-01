%{
    #include <stdio.h>
    #include <string.h>
    #include <string>
    #include <map>
    #include <vector>
    #include <iostream>
    #include <iomanip>
    #include "Program.h"
    #include "Location.h"
    #include "Util.h"
    int yylex(void);
    void yyerror(char *);
    Program program;
%}

%union {
    int iVal;
    char *sVal;
}

%token ADD SUB INC DEC MUL DIV MOD SHR SHL AND OR XOR NEG LDL MOV PUSH POP STM LDM IN OUT GETF SETF CMP
CAL JUMP_ALWAYS JUMP_GREATER JUMP_LESS JUMP_GREATEREQUALS JUMP_LESSEQUALS JUMP_EQUALS JUMP_NOTEQUALS
%token <iVal> REGISTER DEVICE INTEGER
%token <sVal> IDENTIFIER STRING

%%

program:
    program instruction
    | program label
    | program literal
    | program '\n'
    |
    ;

instruction:
      ADD REGISTER ',' REGISTER ',' REGISTER { program.addInstruction(I_ADD, $2, $4, $6); }               // $2 + $4 -> $6
    | SUB REGISTER ',' REGISTER ',' REGISTER { program.addInstruction(I_SUB, $2, $4, $6); }               // $2 - $4 -> $6
    | INC REGISTER                           { program.addInstruction(I_MORE, I_MORE, I_INC, $2); }       // $2++
    | DEC REGISTER                           { program.addInstruction(I_MORE, I_MORE, I_DEC, $2); }       // $2--
    | MUL REGISTER ',' REGISTER ',' REGISTER { program.addInstruction(I_MUL, $2, $4, $6); }
    | DIV REGISTER ',' REGISTER ',' REGISTER { program.addInstruction(I_DIV, $2, $4, $6); }
    | MOD REGISTER ',' REGISTER ',' REGISTER { program.addInstruction(I_MOD, $2, $4, $6); }
    | SHR REGISTER ',' REGISTER ',' REGISTER { program.addInstruction(I_SHR, $2, $4, $6); }
    | SHL REGISTER ',' REGISTER ',' REGISTER { program.addInstruction(I_SHL, $2, $4, $6); }
    | AND REGISTER ',' REGISTER ',' REGISTER { program.addInstruction(I_AND, $2, $4, $6); }
    | OR REGISTER ',' REGISTER ',' REGISTER  { program.addInstruction(I_OR,  $2, $4, $6); }
    | XOR REGISTER ',' REGISTER ',' REGISTER { program.addInstruction(I_XOR, $2, $4, $6); }
    | NEG REGISTER ',' REGISTER              { program.addInstruction(I_MORE, I_NEG, $2, $4); }

    | LDL INTEGER ',' REGISTER               { program.addLoadLiteral($2, $4); }
    | LDL IDENTIFIER ',' REGISTER            { program.addLoadAddress($2, $4); }
    | MOV REGISTER ',' REGISTER              { program.addInstruction(I_MORE, I_MOV, $2, $4); }

    | PUSH REGISTER ',' REGISTER             { program.addInstruction(I_MORE, I_STI, $2, $4); }
    | POP REGISTER ',' REGISTER              { program.addInstruction(I_MORE, I_DLD, $2, $4); }
    | STM REGISTER ',' REGISTER              { program.addInstruction(I_MORE, I_STM, $2, $4); }
    | LDM REGISTER ',' REGISTER              { program.addInstruction(I_MORE, I_LDM, $2, $4); }

    | IN DEVICE ',' REGISTER                 { program.addInstruction(I_MORE, I_IOI, $2, $4); }
    | OUT REGISTER ',' DEVICE                { program.addInstruction(I_MORE, I_IOO, $2, $4); }

    | GETF REGISTER                          { program.addInstruction(I_MORE, I_MORE, I_GTF, $2); }
    | SETF REGISTER                          { program.addInstruction(I_MORE, I_MORE, I_STF, $2); }
    | CMP REGISTER ',' REGISTER              { program.addInstruction(I_MORE, I_CMP, $2, $4); }

    | CAL REGISTER ',' REGISTER              { program.addInstruction(I_MORE, I_CAL, $2, $4); }
    | JUMP_ALWAYS REGISTER                   { program.addInstruction(I_MORE, I_JMP, J_A,  $2); }
    | JUMP_GREATER REGISTER                  { program.addInstruction(I_MORE, I_JMP, J_GT, $2); }
    | JUMP_LESS REGISTER                     { program.addInstruction(I_MORE, I_JMP, J_LT, $2); }
    | JUMP_GREATEREQUALS REGISTER            { program.addInstruction(I_MORE, I_JMP, J_GE, $2); }
    | JUMP_LESSEQUALS REGISTER               { program.addInstruction(I_MORE, I_JMP, J_LE, $2); }
    | JUMP_EQUALS REGISTER                   { program.addInstruction(I_MORE, I_JMP, J_EQ, $2); }
    | JUMP_NOTEQUALS REGISTER                { program.addInstruction(I_MORE, I_JMP, J_NE, $2); }
    ;

label:
    IDENTIFIER ':'                           { program.addLabel($1); }
    ;

literal:
      INTEGER                                { program.addLiteralValue($1); }
    | STRING                                 { program.addLiteralString($1); } /* TODO: de-escape characters and use len */
    ;

%%

void yyerror(char *s) {
  fprintf(stderr, "%s\n", s);
}

int main(int argc, char **args) {
    program.start();
    yyparse();
    program.finish();
    std::cout << program.toBinaryString();
    return 0;
}

