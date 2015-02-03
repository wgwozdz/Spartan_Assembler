%{
  #include <stdlib.h>
  void yyerror(char *);
  #include "Assembler.tab.h"
%}
%option yylineno

%%

    /* Instruction keywords */
"add"  { return  ADD; }
"sub"  { return  SUB; }
"inc"  { return  INC; }
"dec"  { return  DEC; }
"mul"  { return  MUL; }
"div"  { return  DIV; }
"mod"  { return  MOD; }
"shr"  { return  SHR; }
"shl"  { return  SHL; }
"and"  { return  AND; }
"or"   { return   OR; }
"xor"  { return  XOR; }
"neg"  { return  NEG; }
"ldl"  { return  LDL; }
"mov"  { return  MOV; }
"push" { return PUSH; }
"pop"  { return  POP; }
"stm"  { return  STM; }
"ldm"  { return  LDM; }
"in"   { return   IN; }
"out"  { return  OUT; }
"getf" { return GETF; }
"setf" { return SETF; }
"cmp"  { return  CMP; }

"cal"  { return  CAL; }
"ja" { return JUMP_ALWAYS; }
"jgt" { return JUMP_GREATER; }
"jlt" { return JUMP_LESS; }
"jge" { return JUMP_GREATEREQUALS; }
"jle" { return JUMP_LESSEQUALS; }
"je" { return JUMP_EQUALS; }
"jne" { return JUMP_NOTEQUALS; }

r[0-9]+ { yylval.iVal = atoi(yytext+1); return REGISTER; }
d[0-9]+ { yylval.iVal = atoi(yytext+1); return DEVICE; }

    /* Label identifiers */
[A-Za-z][A-Za-z0-9_]* { yylval.sVal = strndup(yytext, yyleng); return IDENTIFIER; }

    /* Value identifiers */
[0-9]+ { yylval.iVal = atoi(yytext); return INTEGER; }
\"(\\.|[^\\"])*\" { yylval.sVal = strndup(yytext, yyleng); return STRING; }

"," { return ','; }
":" { return ':'; }

\/\/.*\n ;
"\n" { return '\n'; }
[ \t] ;

.         yyerror("invalid character");

%%

int yywrap(void) {
  return 1;
}

void yyerror(char *s) {
    fprintf(stderr, "line %d: %s\n", yylineno, s);
    exit(0);
}

