%{
#include <stdio.h>
#include <math.h>
#include "variable.h"

void yyerror(char *s)
{
  fputs(s, stderr);  putc('\n', stderr);
}

void showFormula(double value)
{
 if(ceil(value)!=floor(value))
  printf("%f\n", value);
 else 
  printf("%d\n", (int)value);
}

int main(int argc, char *argv[])
{
  printf(">> ");
  yyparse();
}

%}

%union 
{
  double number;
  char string[255];
  double (*fp)(double);//double型の数学関数用
}

%token  <number> CONSTANT
%token  <string> CHARACTER
%token  <fp> FUNCTION
%token  '+'
%token  '('
%token  ')'

%type <number> lines expression formula term primary
%type <string> character

%%
lines
  : /* empty */
  | lines '\n' {printf(">> ");}
  | lines expression '\n' {printf(">> ");}
  | error '\n'       { yyerrok; printf(">> "); }
expression
  : formula { showFormula($1); }
  | character { show_variable($1); }
  | character '=' formula { update_variable($1, $3); }
formula
  : term
  | '-'term  { $$ = -1*$2; }
  | formula '+' term  { $$ = $1 + $3; }
  | formula '-' term  { $$ = $1 - $3; }
term
  : primary
  | FUNCTION '(' formula ')'{ $$ = $1($3); }
  | term '*' primary { $$ = $1 * $3; }
  | term '/' primary { $$ = $1 / $3; }
  | term '%' primary { $$ = fmod($1,$3); }
  | term '^' primary { $$ = pow($1,$3); }
primary
  : CONSTANT 
  | character { if(get_value($1) != NULL){ $$ = *get_value($1);}else{ $$ = 0;} }
  | '(' formula ')'  { $$ = $2; }
character
  : CHARACTER
%%


