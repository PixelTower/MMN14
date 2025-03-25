#include "prepro.h"
#define MAX_CHAR 80

/* Processes an assembly file */
void process_assembly_file(const char *filename)
{
    FILE *fp;
    char line[MAX_CHAR];
    char *cleaned_line;

    printf("Processing assembly file: %s\n", filename);

    /* Open the file for reading */
    fp = fopen(filename, "r");
    if (!fp)
    {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        return;
    }

    /* Read the file line by line */
    while (fgets(line, sizeof(line), fp))
    {
        cleaned_line = line;

        /* Skip leading spaces and tabs */
        while (*cleaned_line == ' ' || *cleaned_line == '\t')
        {
            cleaned_line++;
        }

        /* Ignore comments (lines starting with ';') and empty lines */
        if (*cleaned_line == ';' || *cleaned_line == '\n' || *cleaned_line == '\0')
        {
            continue;
        }

        /* Ensure the line is properly null-terminated */
        cleaned_line[strcspn(cleaned_line, "\n")] = '\0';

        /* Detect macro definitions (lines that start with "mcro" followed by a space/tab or end of line) */
        if (strncmp(cleaned_line, "mcro", 4) == 0 && (cleaned_line[4] == ' ' || cleaned_line[4] == '\t' || cleaned_line[4] == '\0'))
        {
            printf("Macro detected: %s\n", cleaned_line);
        }

        /* Print the processed line */
        printf("Processed line: %s\n", cleaned_line);
    }

    /* Close the file after processing */
    fclose(fp);
}
