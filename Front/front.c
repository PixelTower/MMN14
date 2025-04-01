#include "front.h"
#include <string.h>
#include <ctype.h>

/* Array of valid opcodes, NULL terminated */
static const char *valid_opcodes[] = {"mov", "cmp", "add", "sub", "lea", "not", "clr", "inc", "dec", "jmp", "bne", "red", "prn", "jsr", "rts", "stop", NULL};

int validate_instruction(const char *instruction)
{
    char label[32], opcode[32], operands[128];
    parse_instruction(instruction, label, opcode, operands);
    return is_valid_instruction(opcode);
}

void parse_instruction(const char *line, char *label, char *opcode, char *operands)
{
    /* Basic parsing logic */
    /* ...implementation here... */
}

int is_valid_instruction(const char *opcode)
{
    int i;
    for (i = 0; valid_opcodes[i] != NULL; i++)
    {
        if (strcmp(valid_opcodes[i], opcode) == 0)
            return 1;
    }
    return 0;
}
