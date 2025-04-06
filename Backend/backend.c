#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "backend.h"
#include "data_strct.h"

#define MAX_LABELS 500

/* Symbol table */
static label_struct label_table[MAX_LABELS];
static int label_count = 0;

/* Add label to symbol table */
void register_label(const char *name, int address)
{
    int i;
    if (label_count >= MAX_LABELS)
    {
        fprintf(stderr, "ERROR: Label table is full.\n");
        return;
    }

    /* Check for duplicates */
    for (i = 0; i < label_count; i++)
    {
        if (strcmp(label_table[i].name, name) == 0)
        {
            fprintf(stderr, "ERROR: Duplicate label '%s'.\n", name);
            return;
        }
    }

    strcpy(label_table[label_count].name, name);
    label_table[label_count].address = address;
    label_table[label_count].type = 0; /* 0 = code label */
    label_count++;
}

/* Return number of registered labels */
int get_label_count(void)
{
    return label_count;
}

/* Free symbol table – in case of dynamic version (not needed here) */
void free_label_table(label_struct *table, int count)
{
    /* No dynamic allocation used here, so nothing to free */
}

/* Find address of label in symbol table */
int find_label_address(const char *name)
{
    int i;
    for (i = 0; i < label_count; i++)
    {
        if (strcmp(label_table[i].name, name) == 0)
        {
            return label_table[i].address;
        }
    }

    fprintf(stderr, "ERROR: Label '%s' not found.\n", name);
    return -1;
}
