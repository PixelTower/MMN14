#ifndef GLOBALS_H
#define GLOBALS_H

/* Constant: maximum line length allowed */
#define MAX_LINE_LENGTH 81

/* Constant: maximum length of a label */
#define MAX_LABEL_LENGTH 31

/* Constant: general large buffer size for temporary strings */
#define BIG_NUMBER_CONST 1000

/* Constant: maximum number of instructions */
#define INSTRUCTIONS_COUNT 4

/* Constant: total number of supported opcodes */
#define OPCODES_COUNT 16

/* Constant: number of available registers */
#define REG_COUNT 8

/* Initial value of the instruction counter */
#define IC_INIT_VALUE 100

/* Addressing types */
#define DIRECT_ADDRESSING 0
#define LABEL_ADDRESSING 1
#define REG_ADDRESSING 2

/* Bit shift amounts for encoding machine code */
#define OPCODE_BITS_SHIFT 6
#define DEST_BITS_SHIFT 2
#define SOURCE_BITS_SHIFT 10

#define DEST_BITS_SHIFT_REG 0
#define SOURCE_BITS_SHIFT_REG 5

/* Constant used for identifying a line with both source and destination registers */
#define DOUBLE_REGS_VALUE 512

/* Struct for representing a file location: line number + file name */
typedef struct location {
    int line_num;         
    char *file_name;    
}file_location;

#endif
