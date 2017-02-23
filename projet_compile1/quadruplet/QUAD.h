/**
*   TS.h
*   
*   Declares of quadruplets table   
*
*     compilation projet of SCL langage 
*       with  FLEX and BISON tools 
*   
*   Proposed by  OUSSAMA BOUMAAD and GHERSA LOUCIF 
*
*   
**/

#ifndef QUAD_H
#define QUAD_H 

// varibales declaration 
typedef struct 
{
    char* op; 
    char* operant1;   
    char* operant2;  
    char* resultat;   
} Quadruplet;

Quadruplet quadruplet[1000];

int qc ; 
int tmpcpt;


	// initialization of quad.h variable 
void init_quad();

	// add new quardruplet 
void add_quad(const char* newop,const char* newoperant1,const char* newoperant2,const char* newresultat);


	// show quadruplet table 
void echo_quad() ;

	//	creat temporaire 
char* temporaire();

	// to make $$.name as idf[index] when it come to table 
char* make_table(char* idf, const char* index );

	// add logical quadruplet 
void add_quadL( int op, char* op1, char* op2, char* res);

	// add comarative quadruplet
char* add_quadC( char* booleen, char* op1, char* op2);

	// convert num to char 
char* Cnum(int num);

/**
*	free quadrupet table
*/
void free_quadruplet_table() ;

#endif // QUAD_H