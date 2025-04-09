
#ifndef BACKEND_H
#define BACKEND_H

#include "data_strct.h"

/* Label table management functions */
void register_label(const char *name, int address);
int get_label_count(void);
int find_label_address(const char *name);
void free_label_table(label_struct *table, int count);

/* First pass and second pass execution functions */
/* Executes the first pass on the given file and returns a dynamic label table.
   label_count_out returns the number of labels and error_flag is set to 1 if an error occurs. */
label_struct *exe_first_pass(const char *filename, int *label_count_out, int *error_flag);

/* Executes the second pass, generating the output file (.ob) and updating extern and entry counts.
   error_flag is set to 1 if an error occurs. */
void exe_second_pass(const char *filename, label_struct *table, int label_count,
                     int *error_flag, int *extern_count, int *entry_count);

#endif 
