%{
#include<stdio.h>
int line = 0;
%}

%option noyywrap


LINE    .*\n
%%

{LINE} {printf("%04d %s", line++, yytext);}

%%

int main() {
    yylex();
    return 0;
}
