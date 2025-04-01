#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "preproc.h"
#include "util.h"
#include "globals.h"
#include "handle_text.h"
#include "Errors.h"

/* Removes extra spaces and comments from file, writes result to a temp file */
char *remove_extra_spaces_file(char file_name[]) {
    char *new_file_name;
    char str[BIG_NUMBER_CONST];
    int line_num;
    FILE *fp, *fp_temp;

    fp = fopen(file_name, "r");
    if (fp == NULL) {
        print_internal_error(ERROR_CODE_2);
        return NULL;
    }

    new_file_name = add_new_file(file_name, ".t01");
    if (new_file_name == NULL) {
        abrupt_close(1, "file", fp);
        return NULL;
    }

    fp_temp = fopen(new_file_name, "w");
    if (fp_temp == NULL) {
        abrupt_close(1, "file", fp);
        print_internal_error(ERROR_CODE_7);
        return NULL;
    }

    line_num = 0;
    while (fgets(str, 999, fp) != NULL) {
        line_num++;

        if (strlen(str) > MAX_LINE_LENGTH) {
            location loc;
            loc.file_name = file_name;
            loc.line_num = line_num;
            print_external_error(ERROR_CODE_30, loc);
            fclose(fp);
            fclose(fp_temp);
            return NULL;
        }

        /* Replace comment lines with a newline */
        if (*str == ';') {
            str[0] = '\n';
            str[1] = '\0';
        } else {
            remove_extra_spaces_str(str);
        }

        fprintf(fp_temp, "%s", str);
    }

    fclose(fp);
    fclose(fp_temp);
    return new_file_name;
}

/* Copies a section of text from a file into a string */
char *copy_text(FILE *fp, fpos_t *pos, int length) {
    int i;
    char *str;

    if (fsetpos(fp, pos) != 0) {
        printf("fsetpos in copy_text failed\n");
        return NULL;
    }

    str = handle_malloc((length + 1) * sizeof(char));
    for (i = 0; i < length; i++) {
        str[i] = getc(fp);
    }
    str[i] = '\0';

    fgetpos(fp, pos); /* Save new position */
    return str;
}

/* Removes extra spaces from a string (leading, in-between, trailing) */
void remove_extra_spaces_str(char str[]) {
    int i = 0, j = 0;
    char temp[MAX_LINE_LENGTH];

    /* Skip leading spaces/tabs */
    while (is_space_or_tab(str[i])) {
        i++;
    }

    while (str[i] != '\0') {
        /* Copy word characters */
        while (!is_space_or_tab(str[i]) && str[i] != '\0') {
            temp[j++] = str[i++];
        }

        /* Insert single space if next char is not null */
        if (str[i] != '\0') {
            temp[j++] = ' ';
        }

        /* Skip additional spaces/tabs */
        while (is_space_or_tab(str[i])) {
            i++;
        }
    }

    /* Remove space at end if present */
    if (j > 0 && temp[j - 1] == ' ') {
        j--;
    }

    temp[j] = '\0';
    strcpy(str, temp);
    remove_spaces_next_to_comma(str);
}

/* Returns 1 if character is a space or tab */
int is_space_or_tab(char c) {
    return c == ' ' || c == '\t';
}

/* Removes any spaces next to a comma (before or after) */
void remove_spaces_next_to_comma(char *str) {
    char temp[MAX_LINE_LENGTH];
    int i = 0, j = 0;

    while (str[i] != '\0') {
        if (str[i] == ' ' && (str[i + 1] == ',' || str[i - 1] == ',')) {
            i++;
            continue;
        }

        temp[j++] = str[i++];
    }

    temp[j] = '\0';
    strcpy(str, temp);
}
