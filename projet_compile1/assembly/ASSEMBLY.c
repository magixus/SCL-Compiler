/**
*   ASSEMBLY.h
*   
*   Implements ASSEMBLY functionality    
*
*     compilation projet of SCL langage 
*       with  FLEX and BISON tools 
*   
*   Proposed by  OUSSAMA BOUMAAD and GHERSA LOUCIF 
*
**/

#include <stdio.h>	
#include <stdlib.h>
#include <string.h>

#include "../symbole_table/TS.h"
#include "ASSEMBLY.h"

void generate_Assembly_code()
{
	assembly_file = fopen("scl_assembly.asm","w");
	find_etiq() ;				// find all jump etiq and save theme in a table		
	sort(save_etiq,etiq_index); // to save all etiq before writing assembly code

	generate_delcaration();		// generate data declaration segment 

	fprintf (assembly_file,"PILE SEGMENT  \n 	stack DW 100 dup (?) \nPILE ENDS \n"); // stack segment

	generate_instruction();		// generate Code instructions segment

	fclose(assembly_file ) ;
 }

void generate_delcaration()
{
	fprintf(assembly_file ,"DATA SEGMENT  \n");
	int index ;
	node *nodep;   
    
    for (index = 0; index < HT_SIZE; index++)
    {
        nodep = hasht[index];
        while (nodep)
        {	
        	// simple variables 
	        if (nodep->nature == 1 && nodep->type == 1) fprintf(assembly_file ,"	%s DD  ? \n",nodep->name );
	        if (nodep->nature == 1 && nodep->type == 2) fprintf(assembly_file ,"	%s DQ  ? \n",nodep->name );
	        if (nodep->nature == 1 && nodep->type == 3) fprintf(assembly_file ,"	%s DB  ? \n",nodep->name );

	        // vectors variables 
	        if (nodep->nature == 2 && nodep->type == 1) fprintf(assembly_file ,"	%s DD %d DUP  ? \n",nodep->name, (nodep->size)/4);
	        if (nodep->nature == 2 && nodep->type == 2) fprintf(assembly_file ,"	%s DQ %d DUP  ? \n",nodep->name, (nodep->size)/4);
	        if (nodep->nature == 2 && nodep->type == 3) fprintf(assembly_file ,"	%s DB %d DUP  ? \n",nodep->name, (nodep->size)/4);   
	        nodep = nodep->next ; 	
        }   
       
    }
   
    fprintf(assembly_file ,"DATA ENDS ; fin de declaration \n\n"); 
}


void generate_instruction()
{
	fprintf(assembly_file ,"\nCODE SEGMENT\n");
	fprintf(assembly_file ,"	ASSUME SS:pile\n 	MOV AX,pile\n 	MOV SS, AX\n");
	fprintf(assembly_file ,"\nBEGIN:  \n");
	int index ;
	etiq_index = 0 ;
	char* operation = malloc(sizeof(char*)) ; // to store arithmetic/logical/comparison  operations (+/*-)/((BZ, BNZ, BP, BPZ, BM, BMZ or BR))
	
	for (index = 0; index < qc; ++index)  // great loop to test quadruplet table
	{
		/**
		*	create jum etiq when it's come to create it !!
		*/
		while (index == save_etiq[etiq_index]) ++etiq_index; // escape some recurring  element on save_etiq[etiq_index]
		if (index == save_etiq[etiq_index-1] && index !=0)		
		{
			fprintf(assembly_file, "etiq_%d :\n", save_etiq[etiq_index-1]);
		}

		//  if the first element of quadruplet table is on of {+/*-}
		if ((quadruplet[index].op[0]=='+') || (quadruplet[index].op[0]=='-') || (quadruplet[index].op[0]=='/') || (quadruplet[index].op[0]=='*') )
 		{
			switch (quadruplet[index].op[0])
			{
				case '+' : 	strcpy(operation,"ADD");break ;
				case '*' : 	strcpy(operation,"MUL");break ;
				case '/' :	strcpy(operation,"DIV");break ;
			    case '-' :  strcpy(operation,"SUB");break ;
			}
			if ((quadruplet[index].operant1[0]=='T') && (quadruplet[index].operant2[0]=='T'))
			{
				fprintf(assembly_file,"		POP AX \n");
				fprintf(assembly_file,"		POP BX \n");
				fprintf(assembly_file,"		%s AX,BX \n",operation);
				fprintf(assembly_file,"		PUSH AX\n");
			}
			else if (quadruplet[index].operant1[0]=='T')
				{
					fprintf(assembly_file,"		POP AX \n");
					fprintf(assembly_file,"		%s AX,%s \n",operation, quadruplet[index].operant2);
					fprintf(assembly_file,"		PUSH AX\n");
				}
				else if (quadruplet[index].operant2[0]=='T')
					{

						fprintf(assembly_file,"		POP AX \n");
						fprintf(assembly_file,"		%s AX,%s \n",operation, quadruplet[index].operant1);
						fprintf(assembly_file,"		PUSH AX\n");
					}
					else
					{
						fprintf(assembly_file,"		MOV AX,%s \n",quadruplet[index].operant1);
						fprintf(assembly_file,"		%s AX,%s \n",operation, quadruplet[index].operant2);
						fprintf(assembly_file,"		PUSH AX\n");
					}
		}
		 /**
		 *	otherwise if the first element of quadruplet table is one of (BZ, BNZ, BP, BPZ, BM, BMZ or BR) or ":="
		 */
		else if (quadruplet[index].op[0] == ':')
			{
				if (quadruplet[index].operant1[0]=='T')   // 42 - ( :=  ,  T10  ,     ,  Val2 )
				{
					fprintf(assembly_file,"		POP AX \n");
					fprintf(assembly_file,"		MOV %s, AX\n",quadruplet[index].resultat);
				}
				else if (quadruplet[index].resultat[0]=='T') // 77 - ( :=  ,  0  ,     ,  T21 )
					{
						fprintf(assembly_file,"		MOV AX, %s \n",quadruplet[index].operant1);
						fprintf(assembly_file,"		PUSH AX\n");
					}
					else
					{
						fprintf(assembly_file,"		MOV AX, %s \n",quadruplet[index].operant1);
						fprintf(assembly_file,"		MOV %s, AX \n",quadruplet[index].resultat);
					}
			}
			else if ((quadruplet[index].op[0] == 'B') && ((quadruplet[index].op[1] != 'O'))) // pour esquivé les BOUND
			{
				switch (quadruplet[index].op[1])
				{
					case 'Z' : 	strcpy(operation,"JE");break ;
					case 'N' :  strcpy(operation,"JNE");break ;
					case 'M' : 	(quadruplet[index].op[2] == 'Z')? strcpy(operation,"JLE"):strcpy(operation,"JL");break ;
					case 'P' :	(quadruplet[index].op[2] == 'Z')? strcpy(operation,"JGE"):strcpy(operation,"JG");break ;
					default: break;
				}

				if (quadruplet[index].op[1] != 'R')
				{
					(quadruplet[index].operant2[0]=='T')? fprintf(assembly_file,"		POP AX \n") : fprintf(assembly_file,"		MOV AX, %s \n",quadruplet[index].operant2);
					fprintf(assembly_file,"		CMP AX, 0 \n");
					fprintf(assembly_file,"		%s etiq_%s \n",operation,quadruplet[index].operant1);
				}
				else
				{
					fprintf(assembly_file,"		JMP etiq_%s \n",quadruplet[index].operant1) ;
				}
			}
	}

	// fin de prog principale
	fprintf(assembly_file,"		\n\nMOV ah, 4ch\nint 21h ; fin prog principale\n");		
	fprintf(assembly_file ,"CODE ENDS \nEND BEGIN \n");

}

void find_etiq()
{
	int index ;	
	etiq_index = 0 ;
	for (index = 0; index < qc; ++index)
	{
		if ((quadruplet[index].op[0] == 'B') && ((quadruplet[index].op[1] != 'O')))
		{
			save_etiq[etiq_index] = atoi(quadruplet[index].operant1) ;
			++etiq_index;
		}
	}
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    int x,i,j=1;
    while(j < n){
            for (i = 0 ; i < n - j ; i++){
                if(values[i] > values[i + 1]) {
                    x = values[i] ;
                    values[i] = values[i + 1];
                    values[i + 1] = x ;
                 }
                
            }
            ++j;
    }

    /*for (i = 0; i < n; ++i)
    {
    	printf("%d\n",values[i] );

    }*/
    
}
