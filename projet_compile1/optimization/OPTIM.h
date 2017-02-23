/**
*   OPTIM.h
*   
*   Declares of OPTIMIZATION functions    
*
*     compilation projet of SCL langage 
*       with  FLEX and BISON tools 
*   
*   Proposed by  OUSSAMA BOUMAAD and GHERSA LOUCIF 
*
*   
**/
#ifndef OPTIM_h
#define OPTIM_h value

#include <stdio.h>	

/**
*	 Delete unused identifiers
*/
void delete_unused_idfs();


/**
*	increments idf->used value
*/
void use_idf(const char* idf) ;



#endif // OPTIM_h