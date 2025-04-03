#ifndef PREPROC_H
#define PREPROC_H

#include <stdio.h>
#include "data_strct.h"

/*  Constant limits  */
#define MAX_LINE_LENGTH 81       
#define MAX_LABEL_LENGTH 31
#define BIG_NUMBER_CONST 1000   


/*  Function declarations  */

/* Adds a macro to the list */
void add_to_list(node **head, const char *name, const char *content, int line);

/* Searches for a macro by name */
node *search_list(node *head, const char *name, int *found);

/* Preprocess a file: handles macro expansion */
FILE *preprocess_file(const char *filename);

/* Clears macro list from memory */
void free_macro_list(node *head);

#endif
