/**
*   TS.h
*   
*   Declares of symbols table   
*
*     compilation projet of SCL langage 
*       with  FLEX and BISON tools 
*   
*   Proposed by  OUSSAMA BOUMAAD and GHERSA LOUCIF 
*
*   
**/
 
#ifndef TS_H
#define TS_H

#include <stdbool.h>

// maximum length for an idf
// (e.g., Avalnum1)
#define LENGTH 8

// maximum hash table size
#define HT_SIZE 26



typedef struct node 
{
    char *name  ; // name  of an idfs
    int  nature ; // 0 const / 1 variable / 2 tableau
    int  type   ; // 1 int / 2 float / 3 c har
    int  size   ; // 4 bytes for all types
    int  used   ; // test if idf is used on codes part or not
    struct node *next;
} node;

// hash table 
node *hasht[HT_SIZE];

/**
*  Initialization of a hash table
*/
void init() ;


/**
*  hash function 
*/
int hash(const char *idf);


/**
 * Returns true if name is in hash table else false.
 */
bool check(const char* idf);

/**
 * Insert name  into hash table.  Returns true if successful else false.
 */
void insert(const char* idf, const int newnature, const int newtype, const int newsize);


/**
*  Free hash table of idfs 
*/

void free_hash_table();



/**
*  show all idfs on terminal
*/
void show_table() ;




#endif // TS_H



