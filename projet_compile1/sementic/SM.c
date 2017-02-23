/**
*   SM.c
*   
*   Implements a SM's functionality.
*
*     compilation projet of SCL langage 
*       with  FLEX and BISON tools 
*   
*   Proposed by  OUSSAMA BOUMAAD and GHERSA LOUCIF 
*   
**/

#include "SM.h"
#include "../symbole_table/TS.h"

int yyerror(char* msg) ;


/**
*	Check if the idf has been declared ; this function is used in code part
*/

void Declared(const char* idf)
{
	if (!check(idf)) yyerror("sementic error, idf is undeclared used in this function !");
	
}

/**
*	check if the idf is daclared twice ; this function is user in declaration part
*/

void Double_Declared(const char* idf)
{
	if (check(idf)) yyerror("sementic error, IDF is declared twice!");
}

/**
*	user_const is a function that test if we are trying to change const valeur
*/

void use_const(const char* idf)
{
	if (get_nature(idf) == 0) yyerror("sementic error,  constant couldn\'t be modified ");

									
}


/**
*	Test_type test if one of the idf is character 
*/

void test_type(const int first, const int second) 
{
	if(first == 3 || second == 3 ) yyerror("sementic error, incompabtible types!");
}

/**
*	test if there is not table overflow
*/
void overflow_table(const char* idf, int index)
{	
	if (get_nature(idf)!=2) yyerror("sementic error, idf is not a table");
	
	int test = get_size(idf) /4 ;
	if (index > test ) yyerror("sementic error, table index out of range!");
}

// get idf type

int  get_type(const char *idf)
{
     
    node *newnode ;

    int hashv = hash(idf);
    newnode = hasht[hashv];
    
    while(newnode != NULL) 
    {
        if (strcasecmp(idf, newnode->name) == 0) return newnode->type ;

        else newnode = newnode->next ;
    }
    
    return -1;
}   
/**
*    get table size
*/
int get_size(const char* idf)
{
    node *newnode ;

    int hashv = hash(idf);
    newnode = hasht[hashv];
    
    while(newnode != NULL) 
    {
        if (strcasecmp(idf, newnode->name) == 0) return newnode->size ;

        else newnode = newnode->next ;
    }
    
    return -1;
}


// get idf nature

int get_nature(const char *idf)
{
    node *newnode ;

    int hashv = hash(idf);
    newnode = hasht[hashv];
    
    while(newnode != NULL) 
        if (strcasecmp(idf, newnode->name) == 0) return newnode->nature ;
        else newnode = newnode->next ;
    
    return -1;

}