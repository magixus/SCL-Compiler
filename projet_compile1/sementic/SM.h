/**
*   SM.h
*   
*   Declares of semantic functions     
*
*     compilation projet of SCL langage 
*       with  FLEX and BISON tools 
*   
*   Proposed by  OUSSAMA BOUMAAD and GHERSA LOUCIF 
*
*   
**/

#ifndef SM_H
#define SM_H

#include <stdio.h>	
#include <stdlib.h>

int   sauv_type; // variable to save declarations types
char* sauv_pas ; // variable to save for_instruction's step
char* sauv_idf ; // variable to save for_instruction's idf(variable)
    	
/**
*	Declared function to test if idf is declared or not
*/
void Declared(const char* idf);


/**
*	Double Declaration function to test if idf is declared twice !
*/
void Double_Declared(const char* idf);

/**
*	user_const is a function that test if we are trying to change const valeur
*/
void use_const(const char* idf);

/**
*	Test_type test if to type are the same 
*/
void test_type(const int first, const int second) ;

/**
*	 overflow_table test if table index is great  then it size 
*/
void overflow_table(const char* idf, int index);



/**
*  Get idf nature (const or variable)
*/
int get_nature(const char *idf);


/**
*  Get idf type (intger , float or characater)
*/
int get_type(const char *idf);

/**
*  Get size of table
*/

int get_size(const char* idf);


#endif // SM_H