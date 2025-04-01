/* data_strct.h - Defines linked list node structure for macros */
#ifndef DATA_STRCT_H
#define DATA_STRCT_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* Node structure for macro definitions */
typedef struct node {
    char *name;              /* Macro name */
    char *content;           /* Macro body */
    int line;                /* Line number of definition */
    struct node *next;       /* Pointer to next macro */
} node;

/* Creates a new macro node */
node *make_node(const char *name, const char *content, int line_num);

/* Adds a macro node to the end of the list */
void add_to_list(node **head, const char *name, const char *content, int line_num);

/* Frees the entire macro list */
void free_macro_list(node *head);

/* Searches the macro list for a given name */
node *search_list(node *head, const char *name, int *found);

#endif /* DATA_STRCT_H */
