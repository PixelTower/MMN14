#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "code_conversion.h"
#include "Errors.h"
#include "globals.h"
#include "table.h"
#include "util.h"
#include "lexer.h"

// Expands the memory of the code array to store a new word
int inc_mem(code_conv **code, int counter) {
    code_conv *ptr;
    ptr = *code;

    // Reallocate memory for one more code word
    *code = realloc(*code, (counter + 1) * sizeof(code_conv));
    if (*code == NULL) {
        print_internal_error(ERROR_CODE_1);
        free(ptr);
        return 0;
    }
    return 1;
}

// Converts a parsed command into a 12-bit machine code word
unsigned short command_to_short(command_parts *command) {
    unsigned short n_src = 0, n_op = 0, n_dest = 0;

    // Encode source operand
    if (what_reg(command->source) >= 0) {
        n_src = REG_ADDRESSING << SOURCE_BITS_SHIFT;
    } else if (legal_label(command->source)) {
        n_src = LABEL_ADDRESSING << SOURCE_BITS_SHIFT;
    } else if (is_num(command->source)) {
        n_src = DIRECT_ADDRESSING << SOURCE_BITS_SHIFT;
    }

    // Encode destination operand
    if (what_reg(command->dest) >= 0) {
        n_dest = REG_ADDRESSING << DEST_BITS_SHIFT;
    } else if (legal_label(command->dest)) {
        n_dest = LABEL_ADDRESSING << DEST_BITS_SHIFT;
    } else if (is_num(command->dest)) {
        n_dest = DIRECT_ADDRESSING << DEST_BITS_SHIFT;
    }

    // Encode opcode
    n_op = (unsigned short)(command->opcode) << OPCODE_BITS_SHIFT;

    // Combine source, opcode, and destination into a single short value
    return (n_src | n_op | n_dest);
}

// Encodes register values into binary representation depending on their position
unsigned short reg_to_short(command_parts *command, int reg_src) {
    static int already_done = 0;
    int reg1 = -1, reg2 = -1;
    unsigned short n_reg_src = 0, n_reg_dest = 0;

    if (reg_src) {
        // Source register
        reg1 = what_reg(command->source);
        if (reg1 >= 0) {
            n_reg_src = reg1 << SOURCE_BITS_SHIFT_REG;
        }
        // Destination register (if exists)
        reg2 = what_reg(command->dest);
        if (reg2 >= 0) {
            n_reg_dest = reg2 << DEST_BITS_SHIFT_REG;
        }
        already_done = 1;
        return n_reg_src | n_reg_dest;
    } else if (already_done == 0) {
        // Handle destination register if not handled yet
        reg2 = what_reg(command->dest);
        if (reg2 >= 0) {
            n_reg_dest = reg2 << DEST_BITS_SHIFT_REG;
        }
        return n_reg_dest;
    }

    already_done = 0;
    return DOUBLE_REGS_VALUE;
}

// Adds a single machine code line to the code array with optional label
int add_machine_code_line(code_conv **code, unsigned short num, char *label, int *IC, location am_file) {
    // Allocate space for new code line
    if (inc_mem(code, *IC) == 0) {
        return 0;
    }

    // Set the binary value and line number
    (*code)[*IC].short_num = num;
    (*code)[*IC].assembly_line = am_file.line_num;

    // Handle label (optional)
    if (label != NULL) {
        (*code)[*IC].label = handle_malloc(strlen(label) + 1);
        if ((*code)[*IC].label == NULL) {
            return 0;
        }
        strcpy((*code)[*IC].label, label);
    } else {
        (*code)[*IC].label = NULL;
    }

    // Move to next instruction
    (*IC)++;
    return 1;
}
