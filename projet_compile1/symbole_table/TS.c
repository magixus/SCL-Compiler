/**
*   TS.c
*   
*   Implements a TS's functionality.
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
#include <strings.h>

#include "TS.h"

// initialisation of hash table 

void init()
{
    int i;
    for (i = 0; i < HT_SIZE; i++) 
    {
        hasht[i] = NULL;
    }
}


// hach function 

int hash(const char *idf) 
{
    int hash = 0;

    hash = idf[0] - 65 ;
     
    return hash ; 
}

// check if name is in identificateur

bool check(const char *idf)
{
    node *newnode ;

    int hashv = hash(idf);

    newnode = hasht[hashv];
    
    while(newnode != NULL)
    {
        if (strcasecmp(idf, newnode->name) == 0) return true ;
        else newnode = newnode->next ;
    }
    return false;

}


// insert idfs into hash table 

void insert(const char *idf, const int newnature, const int newtype, const int newsize)
{
    int hv;    
    node *nodep = malloc(sizeof(node));
    nodep->name = malloc(LENGTH + 1);

    strcpy(nodep->name,idf);
    nodep->type   = newtype ;
    nodep->nature = newnature ;
    nodep->size   = newsize ;
    nodep->used   = 0 ;

    hv = hash(idf);
    
    if(hasht[hv] == NULL)
    {
    	nodep->next = NULL;
        hasht[hv] = nodep;
    }
    else {

	    nodep->next = hasht[hv];
	    hasht[hv] = nodep;
    }
  }
  
//free hash table of idfs
void free_hash_table()
{
    node *nextnodep,*nodep;
    int i;
    
    for (i = 0; i<HT_SIZE; i++)
    {
        nodep = hasht[i];
        while (nodep)
        {
	        free(nodep->name);
	        nextnodep  = nodep->next;
	        free(nodep);
	        nodep = nextnodep;
        }   
        hasht[i] = NULL;
    }
  
}

// cat hash table 

void show_table()
{  
    printf("    ************** La Table des Symboles ********************\n");
    printf("     _______________________________________________________ \n");
    printf("    |   idf       |   nature     |   type      |  size      |\n");


    int i ;

    node *newnode ;

    for ( i = 0; i < HT_SIZE; i++){

        newnode = hasht[i] ;

        while(newnode != NULL) {
            printf("    |-------------|--------------|-------------|------------|\n");

            printf("    |%9s    |%7d       |",newnode->name,newnode->nature);
            
            printf("  %5d      |%7d     | %d\n",newnode->type,newnode->size,newnode->used);
            
            newnode=newnode->next;
        }
    }
    printf("    *-------------------------------------------------------*\n");
}



    

