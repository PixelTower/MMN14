#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "secondpass.h"

extern int DC;
extern int IC;

// פונקציה לביצוע המעבר השני - המרת תוויות לכתובות ובדיקת תקינות
void second_pass(FILE *input, FILE *output)
{
    char line[256];
    rewind(input); // מחזיר את קובץ הקלט להתחלה

    while (fgets(line, sizeof(line), input))
    {
        char *instruction = malloc(32 * sizeof(char));
        char *operand = malloc(128 * sizeof(char));
        if (!instruction || !operand)
        {
            fprintf(stderr, "ERROR: Memory allocation failed\n");
            free(instruction);
            free(operand);
            return;
        }
    }

    int num_tokens = sscanf(line, "%31s %127[^\"]", instruction, operand);
