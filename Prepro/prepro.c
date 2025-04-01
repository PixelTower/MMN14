#include "prepro.h"
#include "util.h"
#include "Errors.h"
#include "data_strct.h"
#include "handle_text.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* Expands macros and creates .am file. Returns pointer to macro list */
node *mcro_exec(const char *file_name) {
    FILE *input_file, *output_file;
    char line[MAX_LINE_LENGTH + 2];
    char *am_file_name;
    node *macro_list = NULL;

    int inside_macro = 0;
    char macro_name[MAX_LABEL_LENGTH];
    char macro_content[BIG_NUMBER_CONST];
    int line_num = 0;

    input_file = fopen(file_name, "r");
    if (!input_file) {
        fprintf(stderr, "[ERROR] Failed to open file: %s\n", file_name);
        return NULL;
    }

    am_file_name = add_new_file(file_name, ".am");
    output_file = fopen(am_file_name, "w");
    if (!output_file) {
        fclose(input_file);
        fprintf(stderr, "[ERROR] Failed to create .am file\n");
        return NULL;
    }

    macro_content[0] = '\0';

    while (fgets(line, sizeof(line), input_file)) {
        char *token;
        char clean_line[MAX_LINE_LENGTH + 2];
        line_num++;

        /* Remove newline and extra spaces */
        line[strcspn(line, "\n")] = '\0';
        strcpy(clean_line, line);
        remove_extra_spaces_str(clean_line);

        if (clean_line[0] == ';' || clean_line[0] == '\0') {
            continue; /* Skip comment or empty line */
        }

        token = strtok(clean_line, " \t");

        /* Start macro definition */
        if (!inside_macro && token && strcmp(token, "mcro") == 0) {
            token = strtok(NULL, " \t");
            if (!token) {
                fprintf(stderr, "[ERROR] Missing macro name at line %d\n", line_num);
                continue;
            }
            strcpy(macro_name, token);
            inside_macro = 1;
            macro_content[0] = '\0';
            continue;
        }

        /* End macro definition */
        if (inside_macro && strcmp(clean_line, "endmcro") == 0) {
            add_to_list(&macro_list, macro_name, macro_content, line_num);
            inside_macro = 0;
            continue;
        }

        /* Inside macro body – accumulate content */
        if (inside_macro) {
            strcat(macro_content, line);
            strcat(macro_content, "\n");
            continue;
        }

        /* Outside macro – check if line is a macro call */
        if (token) {
            int found = 0;
            node *macro = search_list(macro_list, token, &found);
            if (found) {
                fputs(macro->content, output_file);
                continue;
            }
        }

        /* Write regular line */
        fprintf(output_file, "%s\n", line);
    }

    fclose(input_file);
    fclose(output_file);
    return macro_list;
}
