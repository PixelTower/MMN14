#ifndef SECOND_PASS_H
#define SECOND_PASS_H

#include <stdio.h>

/*
 * Performs the second pass of the assembler.
 * This function traverses the instruction AST,
 * resolves labels and outputs the final .ob file.
 */
void second_pass(FILE *output);

/*
 * Writes a single instruction with its resolved address
 * to the output file, in base64 encoding format.
 */
void write_instruction(FILE *output, const char *opcode, int address);

#endif
