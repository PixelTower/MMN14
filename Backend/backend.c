#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "backend.h"
#include "data_strct.h"
#include "Util.h"     /* For add_new_file */
#include "firstpass.h" /* Assumes first_pass is declared here */
#include "secondpass.h"/* Assumes second_pass is declared here */

/* Maximum number of labels */
#define MAX_LABELS 500

/* Static label table and label count */
static label_struct label_table[MAX_LABELS];
static int label_count = 0;

/* Registers a new label if it does not already exist */
void register_label(const char *name, int address) {
    int i;
    if (label_count >= MAX_LABELS) {
        fprintf(stderr, "ERROR: Label table is full.\n");
        return;
    }
    for (i = 0; i < label_count; i++) {
        if (strcmp(label_table[i].name, name) == 0) {
            fprintf(stderr, "ERROR: Duplicate label '%s'.\n", name);
            return;
        }
    }
    /* Copy label name safely */
    strncpy(label_table[label_count].name, name, sizeof(label_table[label_count].name) - 1);
    label_table[label_count].name[sizeof(label_table[label_count].name) - 1] = '\0';
    label_table[label_count].address = address;
    label_table[label_count].type = 0;  /* Example type: 0 = code */
    label_count++;
}

/* Returns the number of registered labels */
int get_label_count(void) {
    return label_count;
}

/* Searches for a label by name and returns its address;
   returns -1 and prints an error if not found */
int find_label_address(const char *name) {
    int i;
    for (i = 0; i < label_count; i++) {
        if (strcmp(label_table[i].name, name) == 0) {
            return label_table[i].address;
        }
    }
    fprintf(stderr, "ERROR: Label '%s' not found.\n", name);
    return -1;
}

/* Frees the dynamically allocated label table */
void free_label_table(label_struct *table, int count) {
    free(table);
}

/* Executes the first pass on the given file.
   It calls first_pass (implemented in firstpass.c) to update the static label_table.
   A dynamic copy of the label table is returned. */
label_struct *exe_first_pass(const char *filename, int *label_count_out, int *error_flag) {
    FILE *fp;
    label_struct *table = NULL;
    int count, i;

    *error_flag = 0;
    fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "ERROR: Cannot open file %s\n", filename);
        *error_flag = 1;
        return NULL;
    }
    /* Run first pass which updates the static label_table */
    first_pass(fp);
    fclose(fp);

    count = get_label_count();
    *label_count_out = count;

    if (count > 0) {
        table = (label_struct *)malloc(count * sizeof(label_struct));
        if (!table) {
            fprintf(stderr, "ERROR: Memory allocation for label table failed.\n");
            *error_flag = 1;
            return NULL;
        }
        for (i = 0; i < count; i++) {
            table[i] = label_table[i];
        }
    } else {
        /* Allocate minimal table if no labels; avoids returning NULL */
        table = (label_struct *)malloc(sizeof(label_struct));
        if (!table) {
            fprintf(stderr, "ERROR: Memory allocation for label table failed.\n");
            *error_flag = 1;
            return NULL;
        }
    }
    return table;
}

/* Executes the second pass: creates the output .ob file and writes machine code.
   Updates error_flag, extern_count, and entry_count as needed.
   Note: second_pass is implemented in secondpass.c.
*/
void exe_second_pass(const char *filename, label_struct *table, int label_count,
                     int *error_flag, int *extern_count, int *entry_count) {
    char *ob_file;
    FILE *fp;

    *error_flag = 0;
    *extern_count = 0;
    *entry_count = 0;

    ob_file = add_new_file(filename, ".ob");
    if (!ob_file) {
        fprintf(stderr, "ERROR: Failed to create .ob file name\n");
        *error_flag = 1;
        return;
    }
    fp = fopen(ob_file, "w");
    if (!fp) {
        fprintf(stderr, "ERROR: Failed to open output file %s\n", ob_file);
        *error_flag = 1;
        free(ob_file);
        return;
    }
    /* Write machine code output to the file */
    second_pass(fp);
    fclose(fp);
    free(ob_file);


}
