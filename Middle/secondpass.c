#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "secondpass.h"
#include "backend.h"
#include "data_strct.h"
#include "util.h"

extern ASTNode *inst_ast;
extern int IC;
extern int DC;

/* Helper function to write instruction to .ob file in base64 */
void write_instruction(FILE *output, const char *opcode, int address)
{
    char *encoded;
    encoded = short_to_base64((unsigned short)address);
    fprintf(output, "%s\t%s\n", opcode, encoded);
    free(encoded);
}

/* Second pass: Resolve labels and write final instructions */
void second_pass(FILE *output)
{
    ASTNode *curr = inst_ast;
    int address = 100; /* Starting memory address */

    while (curr != NULL)
    {
        if (curr->opcode != NULL)
        {
            /* Placeholder: real implementation would resolve operands too */
            write_instruction(output, curr->opcode, address);
            address += 1; /* Increment address for next instruction */
        }
        curr = curr->next;
    }
}
