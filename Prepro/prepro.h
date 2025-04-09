#ifndef PREPROC_H
#define PREPROC_H

#include <stdio.h>
#include "data_strct.h"

/* Constant limits */
#define MAX_LINE_LENGTH 81
#define MAX_LABEL_LENGTH 31
#define BIG_NUMBER_CONST 1000

/* Executes macro preprocessing on a cleaned file */
node *macro_exec(const char *clean_file);

/* Adds a macro to the list */
void add_to_list(node **head, const char *name, const char *content, int line);

/* Searches for a macro by name */
node *search_list(node *head, const char *name, int *found);

/* Clears macro list from memory */
void free_macro_list(node *head);

#endif /* PREPROC_H */
