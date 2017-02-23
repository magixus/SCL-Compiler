%{
#include <stdio.h> 	
#include <string.h>

#include "symbole_table/TS.h"
#include "scl.tab.h"

int yylex();
int yyerror(char* msg);

extern YYSTYPE yylval ;
int colone = 1;
int test_entier = 0 ; 

%}
%option yylineno

chiffre  [0-9]
lettre   [a-zA-Z]
entier {chiffre}+
entier_signer "("(\-|\+){entier}")"
reel {chiffre}+"."{chiffre}*
reel_signer "("(\-|\+){reel}")"
caractere   \'.?\'

idf [A-Z][a-zA-Z0-9]*
commentaire "%%".*



%%

"VAR" 			{colone += yyleng; yylval.chaine =strdup(yytext); return VAR;}
"CODE" 			{colone += yyleng; yylval.chaine =strdup(yytext); return CODE;}
"INTEGER" 		{colone += yyleng; yylval.chaine =strdup(yytext); return INTEGER;}
"FLOAT" 		{colone += yyleng; yylval.chaine =strdup(yytext); return FLOAT;}
"CHAR" 			{colone += yyleng; yylval.chaine =strdup(yytext); return CHAR;}
"CONST" 		{colone += yyleng; yylval.chaine =strdup(yytext); return CONST;}
"VEC"			{colone += yyleng; yylval.chaine =strdup(yytext); return VEC;}

"END" 			{colone += yyleng; yylval.chaine =strdup(yytext); return END;}
"FOR" 			{colone += yyleng; yylval.chaine =strdup(yytext); return FOR;}
"WHILE" 		{colone += yyleng; yylval.chaine =strdup(yytext); return WHILE;}
"IF" 			{colone += yyleng; yylval.chaine =strdup(yytext); return IF;}
"ELSE" 			{colone += yyleng; yylval.chaine =strdup(yytext); return ELSE;}

{idf} 			{colone += yyleng; yylval.chaine =strdup(yytext); return IDF; }
{reel} 			{colone += yyleng; yylval.chaine =strdup(yytext); return FLOATR; }
{reel_signer} 	{colone += yyleng; yylval.chaine =strdup(yytext); return SIGNED_FLOAT; }
{entier} 		{
					test_entier =  atoi(strdup(yytext));
					if(test_entier > 32768)	yyerror("lexical error, integer great then 32768 (out of memory)");
					
					colone += yyleng;					
					yylval.chaine =strdup(yytext); 
					return INT; 
				}
{entier_signer} {
					test_entier =  atoi(strdup(yytext));

					if(test_entier < -32768 || test_entier > 32768 )yyerror("lexical error, integer out of range");
					
					colone += yyleng; 
					yylval.chaine =strdup(yytext);
					return SIGNED_INT; 
				}

{caractere} 	{colone += yyleng; yylval.chaine =strdup(yytext); return CARACTERE; }
{commentaire} 	{}

"=" 			{colone += yyleng; return AFFECT;}
":"	 			{colone += yyleng; return ':';}
"+"	 			{colone += yyleng; return '+';}
"-"	 			{colone += yyleng; return '-';}
"*"	 			{colone += yyleng; return '*';}
"/"	 			{colone += yyleng; return '/';}

">"	 			{colone += yyleng; return '>';}
"<"	 			{colone += yyleng; return '<';}
"=="			{colone += yyleng; return EGAL;}

"!=" 			{colone += yyleng; return DIFF;}
">=" 			{colone += yyleng; return SUPEG;}
"<=" 			{colone += yyleng; return INFEG;}

"&"	 			{colone += yyleng; return ET;}
"||"	 		{colone += yyleng; return OU;}
"!"	 			{colone += yyleng; return '!';}


";"	 			{colone += yyleng; return ';';}

"|"	 			{colone += yyleng; return '|';}
"["	 			{colone += yyleng; return '[';}
"]"	 			{colone += yyleng; return ']';}
"("  			{colone += yyleng; return '(';}
")"  			{colone += yyleng; return ')';}
"}"  			{colone += yyleng; return '}';}
"{"	 			{colone += yyleng; return '{';}
" "  			{colone += yyleng;}
"\t" 			{colone = colone+4 ;}
"\n" 			{colone = 1;}

. 				{yyerror("lexical error, entity dosen't exist ");}

%%

int yywrap()
{
	return 0;
}