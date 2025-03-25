#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "backend.h"

/* Structure to store labels and their addresses */
Label label_table[MAX_LABEL];
int label_count = 0;  /* Number of labels stored */
int next_address = 0; /* Tracks the next available memory address */

/* Adds a label to the table if it's valid and unique */
void register_label(const char *line)
{
    char *delimiter = strrchr(line, ':');
    if (!delimiter)
    {
        return;
    }

    size_t name_length = delimiter - line;
    if (name_length == 0 || name_length >= MAX_LABEL || label_count >= MAX_LABEL)
    {
        fprintf(stderr, "ERROR: Invalid label or label table full\n");
        return;
    }

    char label[MAX_LABEL];
    strncpy(label, line, name_length);
    label[name_length] = '\0';

    for (int i = 0; i < label_count; i++)
    {
        if (strcmp(label_table[i].name, label) == 0)
        {
            fprintf(stderr, "ERROR: Label already exists: %s\n", label);
            return;
        }
    }

    strcpy(label_table[label_count].name, label);
    label_table[label_count].address = next_address;

    label_count++;
    next_address += 4;
}

/* Retrieves the memory address of a specific label */
int find_label_address(const char *label)
{
    for (int i = 0; i < label_count; i++)
    {
        if (strcmp(label_table[i].name, label) == 0)
        {
            return label_table[i].address;
        }
    }

    fprintf(stderr, "ERROR: Label not found: %s\n", label);
    return -1;
}