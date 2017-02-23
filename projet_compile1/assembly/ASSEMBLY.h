/**
*   ASSEMBLY.h
*   
*   Declares ASSEMBLY functions     
*
*     compilation projet of SCL langage 
*       with  FLEX and BISON tools 
*   
*   Proposed by  OUSSAMA BOUMAAD and GHERSA LOUCIF 
*
*   
**/
#ifndef ASSEMBLY_H
#define ASSEMBLY_H

#include "../quadruplet/QUAD.h"

FILE* assembly_file;
int etiq_index ;
int	save_etiq [200] ;


/**
*	declaration assembly code
*/
void generate_delcaration();

/**
 *	instruction assembly code
 */
void generate_instruction();

/**
*	global generate_assembly code function
*/
void generate_Assembly_code ();

/**
*	find all jump etiq
*/
void find_etiq() ;

/**
*	sort jump etiq table	
*/
void sort(int values[], int n) ;


#endif // ASSEMBLY_H