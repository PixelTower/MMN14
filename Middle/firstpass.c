#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "firstpass.h"

int IC = 0; /* Instruction Counter */
int DC = 0; /* Data Counter */

/* Function to check label name validity */
int is_valid_label(const char *label)
{
    int i = 0;
    if (!isalpha(label[0]))
        return 0; /* Label must start with a letter */
    for (i = 1; label[i] != '\0'; i++)
    {
        if (!isalnum(label[i]))
            return 0; /* Label can only contain letters and numbers */
    }
    return 1;
}

/* Function to determine the size of .data or .string variable */
int calculate_data_size(const char *line)
{
    if (strncmp(line, ".string", 7) == 0)
    {
        char *start = strchr(line, '\"');
        if (!start)
            return 0; /* No opening quote found */

        char *end = strchr(start + 1, '\"');
        if (!end)
            return 0; /* No closing quote found */

        return (end - start - 1) + 1; /* String length + null terminator */
    }
    return 4; /* For .data we assume each variable takes 4 bytes */
}

/* Function to calculate instruction size */
int get_instruction_size(const char *line)
{
    return 4; /* Assume each regular instruction takes 4 bytes */
}

/* Function to perform the first pass - collecting labels and setting addresses */
void first_pass(FILE *input)
{
    char line[256];
    rewind(input); /* Reset input file to beginning */

    while (fgets(line, sizeof(line), input))
    {
        /* Remove newline character */
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
        {
            line[len - 1] = '\0';
        }

        /* Skip empty lines or comments */
        if (line[0] == '\0' || line[0] == ';')
        {
            continue;
        }

        /* Remove leading whitespace */
        char *trimmed_line = line;
        while (*trimmed_line && isspace(*trimmed_line))
        {
            trimmed_line++;
        }

        /* Identify and store labels */
        char *colon = strchr(trimmed_line, ':');
        if (colon)
        {
            *colon = '\0'; /* Remove the colon */

            if (!is_valid_label(trimmed_line))
            {
                fprintf(stderr, "ERROR: Invalid label name: %s\n", trimmed_line);
                continue;
            }

            register_label(trimmed_line, IC); /* Register label with current IC address */

            /* Check if there's an instruction after the label */
            char *instruction_part = colon + 1;
            while (*instruction_part && isspace(*instruction_part))
            {
                instruction_part++;
            }

            if (*instruction_part != '\0')
            {
                IC = IC + get_instruction_size(instruction_part);
            }
        }
        else
        {
            /* If it's a variable (.data or .string directive), update DC */
            if (strncmp(trimmed_line, ".data", 5) == 0 || strncmp(trimmed_line, ".string", 7) == 0)
            {
                DC += calculate_data_size(trimmed_line);
            }
            else
            {
                /* Identify instructions and increase IC according to instruction size */
                IC += get_instruction_size(trimmed_line);
            }
        }
    }

    printf("First pass completed. IC = %d, DC = %d, Total labels: %d\n", IC, DC, get_label_count());
}
