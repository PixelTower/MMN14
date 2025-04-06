#ifndef LEXER_H
#define LEXER_H

#include "globals.h"
#include "code_conversion.h"

/* Struct for opcode name and argument count */
typedef struct op_code {
    char *opcode;
    int arg_num;
} op_code;

/* Checks if a string is a valid instruction like .data, .string, etc. */
int is_instr(char *str);

/* Returns index of a valid opcode, or -1 if not found */
int what_opcode(char *str);

/* Returns index of a valid register, or -1 if not found */
int what_reg(char *str);

/* Checks if a string is a valid label declaration ending with ':' */
int legal_label_decl(char *str, int *error_code);

/* Checks if a string is a valid label name (used as operand) */
int legal_label(char *str);

/* Checks if there's extra unexpected text in the line */
int extra_text();

/* Checks if the string is a valid register or label */
int is_reg_or_label(char *str);

/* Checks if the string is a valid number */
int is_num(char *str);

/* Checks if the string is a valid register, label, or number */
int is_reg_or_label_or_num(char *str);

/* Counts how many times a character appears in a string */
int count_occurr(char *str, char ch);

/* Checks if the string contains any whitespace characters */
int has_white_space(const char *str);

/* Verifies if register is legal and sets error code if not */
void check_reg_error(int *error_code, char *str);

/* Checks if file has lines exceeding max length */
int lines_too_long(char *file_name);

#endif
