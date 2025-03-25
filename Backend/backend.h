#ifndef LABEL_MANAGER_H
#define LABEL_MANAGER_H

#define MAX_LABEL 50

/* Structure to store labels and their addresses */
typedef struct
{
    char name[MAX_LABEL];
    int address;
} Label;

/* Function declarations */
void register_label(const char *line);
int find_label_address(const char *label);

#endif /* LABEL_MANAGER_H */