%option noyywrap
%{
#include "calc.tab.h"
#include <stdlib.h>
%}

letter  [a-zA-Z_]
digit        [0-9]
white_blank  [ \t]
other        .|\n

%%
"exit" { exit(0); }
{white_blank}+
{digit}+          { yylval.number = atoi(yytext); return CONSTANT; }
{letter}+		  { strcpy(yylval.string, yytext); return CHARACTER; }
{other}           { return (int)yytext[0]; } 
