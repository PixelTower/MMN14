/* filepath: /Users/ohadrahum/Documents/GettingStarted/MMN14/Front/front.h */

#ifndef FRONT_H
#define FRONT_H

/* Function to validate assembly instruction syntax */
int validate_instruction(const char *instruction);

/* Function to parse assembly instruction into components */
void parse_instruction(const char *line, char *label, char *opcode, char *operands);

/* Function to check if the instruction is valid */
int is_valid_instruction(const char *opcode);

#endif /* FRONT_H */
