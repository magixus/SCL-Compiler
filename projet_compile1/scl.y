%{
#include <stdio.h>	
#include <stdlib.h>
#include <string.h>
#include "symbole_table/TS.h"
#include "sementic/qSM.h"
#include "quadruplet/QUAD.h"
#include "optimization/OPTIM.h"

int yyerror(char* msg);

extern FILE *yyin;
extern int yylineno;
extern int colone;


	
%}
%union{
	char* chaine;
	struct NT
	{
		int type;
		char* name ; 
	}NT;
	struct cond
	{
		int sauv_fin;
		int sauv_deb ;
	}cond;

}

%token VAR CODE INTEGER FLOAT CHAR CONST VEC END FOR WHILE IF ELSE AFFECT <chaine> IDF CARACTERE FLOATR SIGNED_FLOAT INT SIGNED_INT

%token  ':' ';' '[' ']' '(' ')' '{' '}' '|'
%type <NT> valeur typ exp idf 
%type <cond> first_if second_if first_while second_while first_for second_for
%left OU
%left ET 
%left '>' '<' EGAL DIFF SUPEG INFEG
%left '+' '-' 
%left '*' '/'   
%left '!'

%start scl
%%
scl: IDF '{' VAR '{' declaration '}' CODE '{' instruction '}' '}' {printf("Programme correct \n"); return  0; }

declaration: 	  declare_var ';' declaration 
				| CONST IDF AFFECT valeur ';' declaration  {

																Double_Declared($2);
																insert($2,0,$4.type,4);
																add_quad(":=",$4.name,"",$2); // "
															}
				|
;

declare_var: 	  VEC typ declare_vec 
				| typ declare_simple  
;

declare_simple:   var_simple '|' declare_simple
				| var_simple

;

var_simple:		  IDF 							{
													Double_Declared($1);
													insert($1,1,sauv_type,4); 
												}
;

declare_vec:	  var_vec '|' declare_vec 
				| var_vec 
;

var_vec: 		  IDF '[' INT ']' 				{   
    												Double_Declared($1);
    												insert($1,2,sauv_type,atoi($3)*4);
		    	                    			    add_quad("BOUND","0",$3," ");
		    	                    			    add_quad("ADEC",$1," "," ");
    	                  						}
;

valeur : 	      INT        			{$$.type = 1; $$.name = $1 ; }
				| SIGNED_INT 			{$$.type = 1; $$.name = $1 ; }
				| FLOATR          		{$$.type = 2; $$.name = $1 ; }
				| SIGNED_FLOAT   		{$$.type = 2; $$.name = $1 ; }
				| CARACTERE     		{$$.type = 3; $$.name = $1 ; }
; 

typ:   	          FLOAT					{sauv_type = 2; }
				| CHAR 					{sauv_type = 3; }
				| INTEGER				{sauv_type = 1; }
;

instruction: 	  affect ';' instruction
				| if_instruction instruction
				| while_instruction instruction
				| for_instruction instruction
				|
;

affect: 		  idf AFFECT exp 	{ 	if($1.type == 3 && $3.type != 3) yyerror("sementic error, incompatible types !!");
										if($3.type == 3 && $1.type != 3) yyerror("sementic error, incompatible types !!");
										add_quad(":=",$3.name," ",$1.name);
								 	}
;

idf: 			  IDF 	{ // j'ai fait ça pour afficher exactement la colone d'erreur si elle existe

							Declared($1);
							use_const($1);
							use_idf($1);
							$$.type = get_type($1);
							$$.name = $1 ;
						}	
				| IDF '[' INT ']'	{
										Declared($1);
										overflow_table($1, atoi($3));
										use_idf($1);
										$$.type = get_type($1) ;
										$$.name = make_table(strdup($1),strdup($3));
									}
;

exp: 			  exp '*' exp	{
									test_type($1.type, $3.type);
									if ($1.type == 2) $$.type = 2 ;
									else $$.type = $3.type	;
									$$.name = temporaire();	
									add_quad("*",$1.name,$3.name,$$.name);
								}
				| exp '/' exp	{
									test_type($1.type, $3.type);
									$$.type = 2	;
									$$.name = temporaire();	
									add_quad("/",$1.name,$3.name,$$.name);
								}
				| exp '-' exp	{
									test_type($1.type, $3.type);
									if ($1.type == 2) $$.type = 2 ;
									else $$.type = $3.type	;
									$$.name = temporaire();	
									add_quad("-",$1.name,$3.name,$$.name);
								}
				| exp '+' exp	{	
									test_type($1.type, $3.type);
									if ($1.type == 2) $$.type = 2 ;
									else $$.type = $3.type ;	
									$$.name = temporaire();								
									add_quad("+",$1.name,$3.name,$$.name);	
								}
				| exp OU exp	{	
									test_type($1.type, $3.type);
									$$.type = 1 ;
									$$.name = temporaire();
									add_quadL(1,$1.name,$3.name,$$.name);
								}
				| exp ET exp	{
									test_type($1.type, $3.type);
									$$.type = 1 ;
									$$.name = temporaire();
									add_quadL(2,$1.name,$3.name,$$.name);	
								}
				| '!' exp		{	
									test_type($2.type, 1);
									$$.type = 1 ;
									$$.name = temporaire();
									add_quadL(3,$2.name," ",$$.name);
								}
				| exp '>' exp	{
									test_type($1.type, $3.type);
									$$.type = 1 ;
									$$.name = add_quadC("BP",$1.name,$3.name);									
								}
				| exp '<' exp	{
									test_type($1.type, $3.type);
									$$.type = 1 ;
									$$.name = add_quadC("BM",$1.name,$3.name);	
								}
				| exp DIFF exp	{
									test_type($1.type, $3.type);
									$$.type = 1 ;
									$$.name = add_quadC("BNZ",$1.name,$3.name);	
								}
				| exp SUPEG exp	{
									test_type($1.type, $3.type);
									$$.type = 1 ;
									$$.name = add_quadC("BPZ",$1.name,$3.name);	
								}
				| exp INFEG exp	{
									test_type($1.type, $3.type);
									$$.type = 1 ;
									$$.name = add_quadC("BMZ",$1.name,$3.name);	
								}
				| exp EGAL exp	{
									test_type($1.type, $3.type);
									$$.type = 1 ;
									$$.name = add_quadC("BZ",$1.name,$3.name);	
								}
				
				| '(' exp ')'		{
										$$.type = $2.type ;
										$$.name = $2.name ; 
									}
				| IDF 				{		
										Declared($1); 
										use_idf($1);
										$$.type = get_type($1);
										$$.name = $1 ; 
									}
				| IDF '[' INT ']'	{
										Declared($1); 
										overflow_table($1, atoi($3));
										use_idf($1);
										$$.type = get_type($1) ;
										$$.name = make_table(strdup($1),strdup($3));
									}
				| valeur			{
										$$.type = $1.type ;
										$$.name = $1.name ;
									}
;

if_instruction:     first_if instruction END 		{
													// END if_instruction --> update BR  
													strcpy(quadruplet[$1.sauv_fin].operant1,Cnum(qc)) ;
												}
;
first_if:		  second_if instruction	ELSE	{
													$$.sauv_fin = qc ;
													add_quad("BR","","","");

													// BEGIN of ELSE so -> update condition jump
													strcpy(quadruplet[$1.sauv_deb].operant1 ,Cnum(qc));
												} 
;
second_if: 		  IF '(' exp ')' ':'			{
													$$.sauv_deb = qc ;
													add_quad("BZ","",$3.name,"");
												} 
;

while_instruction: 	first_while instruction END 	{
														add_quad("BR",Cnum($1.sauv_deb),"","");
														strcpy(quadruplet[$1.sauv_fin].operant1,Cnum(qc)) ;
														
													}
;
first_while: 	 	second_while '(' exp ')' 		{
														$$.sauv_fin = qc ;
														add_quad("BZ","",$3.name,"");	
														$$.sauv_deb = $1.sauv_deb ;
													}	
;
second_while:		WHILE 							{
														$$.sauv_deb = qc ;
													}
;

for_instruction: 	first_for instruction END 		{
														add_quad("+",sauv_pas,sauv_idf,sauv_idf);
														add_quad("BR",Cnum($1.sauv_deb),"","");
														strcpy(quadruplet[$1.sauv_fin].operant1,Cnum(qc)) ;
														
													}
;																													
first_for: 			second_for exp ')'				{
														$$.sauv_fin = qc ;
														$$.sauv_deb = $1.sauv_deb ;
														add_quad("BZ","",$2.name,"");	
													}															
;																
second_for:			FOR '(' IDF ':' INT ':'			{
														Declared($3);
														use_const($3);
														if (get_type($3) != 1) yyerror("sementic error, idf must be integer !");
														$$.sauv_deb = qc ;
														sauv_pas = strdup($5);
														sauv_idf = strdup($3);														
													}								
;


						
%%


int yyerror(char* msg){

	char* type_error = malloc(sizeof(char*));
	char* error      = malloc(sizeof(char*));
	 size_t i;
    for (i = 0; i < strlen(msg) && msg[i] != ','; i++) type_error[i] = msg[i] ;    
    type_error[i] = '\0';i++ ;
    for (; i < strlen(msg); i++) error[i-strlen(type_error)-1] = msg[i] ;    

	printf("%s , line %d , colone %d : %s\n",type_error, yylineno,colone,error);
	free(type_error); free(error);
	exit(EXIT_FAILURE);
}
	
int main(){

	yyin = fopen("file.scl","r");
	init_quad();
	yyparse();

	show_table(); // before delete_unused_idfs ;
		delete_unused_idfs() ;
	show_table(); // before delete_unused_idfs ;
	
	echo_quad() ;
	generate_Assembly_code(); 

	free_hash_table(); // for free all symbole table elements
	free_quadruplet_table() ;
	
	return 0;
}
