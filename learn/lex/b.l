%{
int lines = 0;
int chars = 0;
int digits = 0;
%}

%option noyywrap

DIGIT [0-9]

%%
{DIGIT}+ {++digits;}
\n  ++lines; ++chars;
.   ++chars;
%%

int main(int argc, char *argv[])
{
    argc--; argv++;
    if(argc > 0) {
        yyin = fopen(argv[0], "r");
    } else {
        yyin = stdin;
    }

	yylex();
    printf("lines:%d chars:%d digits:%d\n", lines, chars, digits);
    if(yyin != stdin) {
        close(yyin);
    }
	return 0;
}

int yywap() {
    return 1;
}
