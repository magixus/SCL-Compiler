/**
*   TS.h
*   
*   implementation  of quadruplets functionality   
*
*     compilation projet of SCL langage 
*       with  FLEX and BISON tools 
*   
*   Proposed by  OUSSAMA BOUMAAD and GHERSA LOUCIF 
*
*   
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "QUAD.h"

void init_quad()
{
	qc = 0 ; 
	tmpcpt = 0;
}

void add_quad(const char* newop,const char* newoperant1,const char* newoperant2,const char* newresultat)
{
	quadruplet[qc].op		=	malloc(sizeof(char*));
	quadruplet[qc].operant1 =	malloc(sizeof(char*));
	quadruplet[qc].operant2 =	malloc(sizeof(char*));
	quadruplet[qc].resultat =	malloc(sizeof(char*));

	strcpy(quadruplet[qc].op,newop);
	strcpy(quadruplet[qc].operant1,newoperant1); 
	strcpy(quadruplet[qc].operant2,newoperant2); 
	strcpy(quadruplet[qc].resultat,newresultat);
	qc++;
}

void echo_quad() 
{
	int j;
	FILE* yyout_quadruple=NULL;
	yyout_quadruple=fopen("quadruplet.txt","w");

	    if (yyout_quadruple!=NULL)
	    {
	    	for (j=0;j<qc;j++)
	        {	
			    fprintf(yyout_quadruple,"%d - ( %s  ,  %s  ,  %s  ,  %s )\n",j, quadruplet[j].op,quadruplet[j].operant1,quadruplet[j].operant2, quadruplet[j].resultat);
		    } 
		    fprintf(yyout_quadruple, "%d -\n", j);
		    fclose(yyout_quadruple);
	    }
	    else
	    {
	    	printf("Impossible d'ouvrir le fichier quadruplet.txt");
	    }
	
}

void add_quadL( int op, char* op1, char* op2, char* res)
{
	switch (op)
	{
		// OU 
		case 1:		add_quad("BNZ",Cnum(qc+4),op1," ");
					add_quad("BNZ",Cnum(qc+3),op2," ");
					add_quad(":=",Cnum(0)," ",res);
					add_quad("BR",Cnum(qc+2)," "," ");
					add_quad(":=",Cnum(1)," ",res);break ;
		// ET
		case 2:		add_quad("BZ",Cnum(qc+4),op1," ");
					add_quad("BZ",Cnum(qc+3),op2," ");
					add_quad(":=",Cnum(1)," ",res);
					add_quad("BR",Cnum(qc+2)," "," ");
					add_quad(":=",Cnum(0)," ",res);break ;
		// NOT (!exp)
		case 3:		add_quad("BZ",Cnum(qc+3),op1," ");
					add_quad(":=",Cnum(0)," ",res);
					add_quad("BR",Cnum(qc+2)," "," ");
					add_quad(":=",Cnum(1)," ",res);break;
	}
}

char* add_quadC( char* booleen, char* op1, char* op2)
{	
	char* tmp = temporaire();

	add_quad("-",op1,op2,tmp);
	add_quad(booleen,Cnum(qc+3),tmp," ");
	tmp = temporaire();
	add_quad(":=",Cnum(0)," ",tmp);
	add_quad("BR",Cnum(qc+2)," "," ");
	add_quad(":=",Cnum(1)," ",tmp);

	return tmp ;
}

char* Cnum(int number){
	char* num = malloc(sizeof(char*));
	sprintf(num, "%d", number);
	return num ;
}

char* temporaire(){
	char* temp =malloc(sizeof(char*));
	sprintf(temp,"T%d",++tmpcpt);
	return temp ;

}


char* make_table(char* idf, const char* index )
{
	char* c = idf;
	c = strcat(c,"[");
	c = strcat(c,index);
	c = strcat(c,"]");

	return c ;

}

/**
*	fonctin de libératin de la table des quadruplets 
*/

void free_quadruplet_table()
{
    
    int i;
    
    for (i = 0; i< qc; i++)
    {
        free(quadruplet[i].op);
        free(quadruplet[i].operant1);
        free(quadruplet[i].operant2);
        free(quadruplet[i].resultat);
    }
  
}