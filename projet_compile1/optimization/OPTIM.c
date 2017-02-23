/**
*   OPTIM.c
*   
*   Implements a OPTIMIZATION's functionality.
*
*     compilation projet of SCL langage 
*       with  FLEX and BISON tools 
*   
*   Proposed by  OUSSAMA BOUMAAD and GHERSA LOUCIF 
*   
**/
#include <stdlib.h>
#include "../symbole_table/TS.h"
#include "OPTIM.h"


void delete_unused_idfs()
{  
    int i ;
    node *current_node, *precedent_node ;

    for ( i = 0; i < HT_SIZE; i++){

        current_node = hasht[i] ;
        precedent_node = current_node ;

        while(current_node != NULL) {
            if (current_node->used == 0) // if this element in not unsed during the programm
            {
            	printf("%s is not used ---> it will be deleted\n", current_node->name);
            	if(current_node == hasht[i]) // if the element to delete is the first one to delete
            	{
            		if (current_node->next == NULL) // if this element is the only one on this (i)th table cell list 
            		{
            		 	hasht[i] = NULL ;
            		 	free(current_node->name);
            		 	free(current_node);
            			break;
            		}else // else if there is other element on this this (i)th table cell list 
            		{
            			hasht[i] = current_node->next ;
            			free(current_node->name);
            		 	free(current_node);
            			current_node = hasht[i] ;
            		}
            	}else // else if the element to delete is in the middle of this (i)th table cell list
            	{
	            	precedent_node->next = current_node->next ;
	            	free(current_node->name);
            		free(current_node);
	            	current_node = precedent_node->next ;
	            }
            	
            }
        	else 
        	{
        		precedent_node = current_node ;
        		current_node = current_node->next ;
        	}
        }
    }
}

void use_idf(const char* idf) 
{
    node *newnode ;

    int hashv = hash(idf);
    newnode = hasht[hashv];
    
    while(newnode != NULL) 
    {
        if (strcasecmp(idf, newnode->name) == 0) 
            { 
                ++newnode->used ; 
                break ;
            }

        newnode = newnode->next ;
    }
}
   
    