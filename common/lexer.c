#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "lexer.h"
#include "globals.h"
#include "Errors.h"

/* List of supported opcodes and their expected number of arguments */
op_code OPCODES[] = {
    {"mov",  2}, {"cmp",  2}, {"add",  2}, {"sub",  2},
    {"not",  1}, {"clr",  1}, {"lea",  2}, {"inc",  1},
    {"dec",  1}, {"jmp",  1}, {"bne",  1}, {"red",  1},
    {"prn",  1}, {"jsr",  1}, {"rts",  0}, {"stop", 0}
};

/* List of valid registers */
char *REGS[] = {"@r0", "@r1", "@r2", "@r3", "@r4", "@r5", "@r6", "@r7"};

/* List of assembler instructions (non-opcode) */
char *INSTUCTIONS[] = {".data", ".string", ".extern", ".entry"};

/* Check for lines that are too long in a file */
int lines_too_long(char *file_name) {
    char str[BIG_NUMBER_CONST];
    FILE *fp;
    location loc;
    int too_long = 0;

    fp = fopen(file_name, "r");
    loc.file_name = file_name;
    loc.line_num = 0;

    while (fgets(str, BIG_NUMBER_CONST, fp) != NULL) {
        loc.line_num++;
        if (strlen(str) > MAX_LINE_LENGTH) {
            print_external_error(ERROR_CODE_30, loc);
            too_long = 1;
        }
    }

    fclose(fp);
    return too_long;
}

/* Check if a string is a valid instruction like .data or .entry */
int is_instr(char *str) {
    int i;
    if (str == NULL)
        return 0;

    for (i = 0; i < INSTRUCTIONS_COUNT; i++) {
        if (strcmp(str, INSTUCTIONS[i]) == 0)
            return 1;
    }
    return 0;
}

/* Return the index of a valid opcode, or -1 if invalid */
int what_opcode(char *str) {
    int i;
    if (str == NULL)
        return -1;

    for (i = 0; i < OPCODES_COUNT; i++) {
        if (strcmp(str, OPCODES[i].opcode) == 0)
            return i;
    }
    return -1;
}

/* Return the index of a register, or -1 if invalid */
int what_reg(char *str) {
    int i;
    if (str == NULL)
        return -1;

    for (i = 0; i < REG_COUNT; i++) {
        if (strcmp(str, REGS[i]) == 0)
            return i;
    }
    return -1;
}

/* Check if a string is a valid label declaration (ending with ':') */
int legal_label_decl(char *str, int *error_code) {
    if (str == NULL)
        return 0;

    if (strlen(str) > MAX_LABEL_LENGTH || !isalpha(*str) || what_reg(str) >= 0) {
        *error_code = ERROR_CODE_44;
        return 0;
    }

    if (what_opcode(str) < 0) {
        while (*(++str) != '\0' && (isalpha(*str) || isdigit(*str))) ;
        if (*str == ':' && *(str + 1) == '\0') {
            *str = '\0';
            return 1;
        } else {
            *error_code = ERROR_CODE_44;
        }
    }

    return 0;
}

/* Check if a string is a valid label (without ':') */
int legal_label(char *str) {
    if (str == NULL)
        return 0;

    if (isalpha(*str) && strlen(str) <= MAX_LABEL_LENGTH &&
        what_opcode(str) < 0 && !is_instr(str)) {
        while (*(++str) != '\0' && *(str) != ' ' &&
               (isalpha(*str) || isdigit(*str))) ;
    }

    return (*str == '\0' || *str == ' ');
}

/* Check if there is unexpected extra text after expected tokens */
int extra_text() {
    char *token = strtok(NULL, "\n");
    return token != NULL;
}

/* Return 1 if string is a register or label, 0 otherwise */
int is_reg_or_label(char *str) {
    return (what_reg(str) >= 0) || legal_label(str);
}

/* Return 1 if string is numeric */
int is_num(char *str) {
    char *ptr;
    if (str != NULL) {
        strtol(str, &ptr, 10);
        return (*ptr == '\0' || *ptr == ' ');
    }
    return 0;
}

/* Return 1 if string is a register, label, or number */
int is_reg_or_label_or_num(char *str) {
    return is_reg_or_label(str) || is_num(str);
}

/* Count the number of occurrences of a specific character in a string */
int count_occurr(char *str, char ch) {
    int count = 0;
    char *ptr = str;
    while ((*ptr != '\0') && (ptr = strchr(ptr, ch)) != NULL) {
        count++;
        ptr++;
    }
    return count;
}

/* Check if the string contains any whitespace characters */
int has_white_space(const char *str) {
    while (*str) {
        if (isspace(*str))
            return 1;
        str++;
    }
    return 0;
}

/* Check if register name is legal, and set error code if not */
void check_reg_error(int *error_code, char *str) {
    char temp_str[MAX_LINE_LENGTH];

    if (error_code[0])
        return;

    strcpy(temp_str, str);

    if (has_white_space(str)) {
        *error_code = ERROR_CODE_33;
    } else if (atoi(strtok(temp_str, "@r"))) {
        *error_code = ERROR_CODE_46;
    } else {
        *error_code = ERROR_CODE_33;
    }
}
