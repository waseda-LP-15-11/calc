%{
#include <stdio.h>
#include <limits.h>
#include "exmath.h"
#include "variable.h"
#include "arithmetic.h"

void yyerror(char *s)
{
  fputs(s, stderr);  putc('\n', stderr);
}

void showFormula(double value)
{

  if(isinf(value))//オーバーフロー
  {
    printf("INFINITY\n");
    return;
  }

  if(isnan(value))//数値でない
  {
    printf("Not a Number\n");
    return;
  }

 if(ceil(value)!=floor(value) || value > INT_MAX)
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
  double (*fp)(double);//引数が1つの数学関数用
  double (*fpp)(double,double);//引数が2つの数学関数用
}

%token  <number> CONSTANT
%token  <string> CHARACTER
%token  <fp> FUNCTION
%token  <fpp> FUNCTION2
%token  '+'
%token  '('
%token  ')'

%type <number> lines expression formula term primary
%type <string> character

%%
lines
  : /* empty */ {}
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
  | formula '+' term  { $$ = add($1, $3); }
  | formula '-' term  { $$ = sub($1, $3); }
term
  : primary
  | term '*' primary { $$ = multiple($1, $3); }
  | term '/' primary { $$ = divide($1, $3); }
  | term '%' primary { $$ = fmod($1,$3); }
  | term '^' primary { $$ = pow_with_check_overflow($1,$3); }
primary
  : CONSTANT 
  | FUNCTION '(' formula ')'{ $$ = $1($3); }
  | FUNCTION2 '(' formula','formula')'{ $$ = $1($3,$5); }
  | character { if(get_value($1) != NULL){ $$ = *get_value($1);}else{ $$ = 0;} }
  | '(' formula ')'  { $$ = $2; }
character
  : CHARACTER
%%


