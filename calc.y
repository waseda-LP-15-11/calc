%{
#include <stdio.h>
#include "variable.h"

void yyerror(char *s){
  fputs(s, stderr);  putc('\n', stderr);
}

int main(int argc, char *argv[]){
  yyparse();
  printf("done!\n");
}

%}

%defines
%union {
  int number;
  char string[255];
}

%token  <number> CONSTANT
%token  <string> CHARACTER
%token  '+'
%token  '('
%token  ')'

%type <number> lines expression formula term primary
%type <string> character

%%
lines
  : /* empty */ 
  | lines '\n'
  | lines expression '\n'
  | error '\n'       { yyerrok; }
expression
  : formula { printf("%d\n", $1); }
  | character { show_variable($1); }
  | character '=' primary { update_variable($1, $3); }
formula
  : term  
  | formula '+' term  { $$ = $1 + $3; }
  | formula '-' term  { $$ = $1 - $3; }
term
  : primary
  | term '*' primary { $$ = $1 * $3; }
  | term '/' primary { $$ = $1 / $3; }
  | term '%' primary { $$ = $1 % $3; }
primary
  : CONSTANT 
  | character { if(get_value($1) != NULL){ $$ = *get_value($1);}else{ $$ = 0;} }
  | '(' formula ')'  { $$ = $2; }
character
  : CHARACTER
%%


