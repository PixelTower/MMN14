#ifndef BACKEND_H
#define BACKEND_H

#include "data_strct.h"

void register_label(const char *name, int address);
int get_label_count(void);
int find_label_address(const char *name);
void free_label_table(label_struct *table, int count);

label_struct *exe_first_pass(const char *filename, int *label_count, int *error_flag);
void exe_second_pass(const char *filename, label_struct *table, int label_count,
                     int *error_flag, int *extern_count, int *entry_count);

#endif
