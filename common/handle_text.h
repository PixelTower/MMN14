#ifndef HANDLE_TEXT_H
#define HANDLE_TEXT_H

#include <stdio.h>

/* Removes extra spaces from the entire file and creates a new cleaned file */
char *remove_extra_spaces_file(char file_name[]);

/* Copies text from a file into a string from a given position and length */
char *copy_text(FILE *fp, fpos_t *pos, int length);

/* Removes leading/trailing and duplicate spaces inside a string */
void remove_extra_spaces_str(char str[]);

/* Checks if the character is a space or tab */
int is_space_or_tab(char c);

/* Removes spaces directly before and after commas */
void remove_spaces_next_to_comma(char *str);

#endif
