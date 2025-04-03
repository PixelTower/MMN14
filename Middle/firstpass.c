#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "firstpass.h"
#include "backend.h"

int IC = 0; /* Instruction Counter */
int DC = 0; /* Data Counter */

/* Function to check label name validity */
int is_valid_label(const char *label)
{
    int i = 0;
    if (!isalpha(label[0]))
        return 0;
    for (i = 1; label[i] != '\0'; i++)
    {
        if (!isalnum(label[i]))
            return 0;
    }
    return 1;
}

/* Function to determine the size of .data or .string variable */
int calculate_data_size(const char *line)
{
    const char *start;
    const char *end;

    if (strncmp(line, ".string", 7) == 0)
    {
        start = strchr(line, '\"');
        if (!start)
            return 0;

        end = strchr(start + 1, '\"');
        if (!end)
            return 0;

        return (end - start - 1) + 1;
    }

    return 4; /* For .data assume 4 bytes per value */
}

/* Function to calculate instruction size */
int get_instruction_size(const char *line)
{
    return 4; /* Placeholder for now */
}

/* First pass: collect labels and compute addresses */
void first_pass(FILE *input)
{
    char line[256];
    char *trimmed_line;
    size_t len;
    char *colon;
    char *instruction_part;

    rewind(input);

    while (fgets(line, sizeof(line), input))
    {
        len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
        {
            line[len - 1] = '\0';
        }

        if (line[0] == '\0' || line[0] == ';')
            continue;

        trimmed_line = line;
        while (*trimmed_line && isspace(*trimmed_line))
            trimmed_line++;

        colon = strchr(trimmed_line, ':');
        if (colon)
        {
            *colon = '\0';

            if (!is_valid_label(trimmed_line))
            {
                fprintf(stderr, "ERROR: Invalid label name: %s\n", trimmed_line);
                continue;
            }

            register_label(trimmed_line, IC);

            instruction_part = colon + 1;
            while (*instruction_part && isspace(*instruction_part))
                instruction_part++;

            if (*instruction_part != '\0')
            {
                IC += get_instruction_size(instruction_part);
            }
        }
        else
        {
            if (strncmp(trimmed_line, ".data", 5) == 0 || strncmp(trimmed_line, ".string", 7) == 0)
            {
                DC += calculate_data_size(trimmed_line);
            }
            else
            {
                IC += get_instruction_size(trimmed_line);
            }
        }
    }

    printf("First pass completed. IC = %d, DC = %d, Total labels: %d\n", IC, DC, get_label_count());
}
