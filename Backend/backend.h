#ifndef BACKEND_H
#define BACKEND_H

#include "data_strct.h"

void register_label(const char *name, int address);
int get_label_count(void);
int find_label_address(const char *name);
void free_label_table(label_struct *table, int count);

#endif
