%{
	#include<stdio.h>
	int ch,word,space,eol;
%}

%%
[a-zA-Z]+	{ch += yyleng; word += 1;};
[ \t]		space += 1;
\n		eol++;
%%

int yywrap() {
	return 1;
}

main(){
	printf("Enter a string\n");
	yylex();
	printf("Char : %d \t Space : %d \t Word : %d \t EOL : %d\n",ch,word,space,eol);
	return 0;
}