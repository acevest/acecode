%{
/*
 * lex 将会将 %{ %} 之间的内容直接拷贝到C程序文件。
 * 所以这之间可以编写任何有效的C代码.
 */

%}

%option noyywrap

%%

[\t ]+	/* 忽略空白行 */ ;
is |
am |
are |
were |
was |
be |
being |
been |
do |
does |
did |
will |
would |
should |
can |
could |
has |
have |
had |
go		{ printf("%s: is a verb\n", yytext); }
[a-zA-Z]+	{ printf("%s: is not a verb\n", yytext); }
[0-9]+		{ printf("%s: is a num\n", yytext); }
.|\n		{ ECHO; /* 通常的默认状态 */ }

%%

int main()
{
	yylex();
	return 0;
}

int yywap() {
    return 1;
}
