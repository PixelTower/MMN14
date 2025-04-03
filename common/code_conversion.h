#ifndef CODE_CONVERSION_H
#define CODE_CONVERSION_H

#include "globals.h"

/* Represents a single line of machine code */
typedef struct code_conv {
    unsigned short short_num;  /* Binary value of the instruction */
    int assembly_line;         /* Line number in the .am file */
    char *label;               /* Label attached to this line, if any */
} code_conv;

/* Represents the parts of a command: source, destination, and opcode */
typedef struct command_parts {
    char *source;  /* Source operand */
    char *dest;    /* Destination operand */
    int opcode;    /* Opcode index */
} command_parts;

/* Allocates or reallocates memory for code array */
int inc_mem(code_conv **code, int counter);

/* Converts a parsed command to a 12-bit binary word */
unsigned short command_to_short(command_parts *command);

/* Converts register(s) to binary depending on whether source or destination */
unsigned short reg_to_short(command_parts *command, int reg_src);

/* Adds a single line to the code array */
int add;

#endif 