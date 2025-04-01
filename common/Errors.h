#ifndef ERRORS_H
#define ERRORS_H

#include <stdio.h>
#include "globals.h"  // For 'location' struct

/**
 * Represents a single error with its code and associated message.
 */
typedef struct Error {
    int error_id;         /* Unique identifier for the error */
    char *error_msg;      /* Message to describe the error */
} Error;

/**
 * Enum for all error codes in the assembler.
 */
typedef enum ERROR_CODES {
    // General & macro-related errors
    ERROR_CODE_0 = 0,
    ERROR_CODE_1,
    ERROR_CODE_2,
    ERROR_CODE_3,
    ERROR_CODE_4,
    ERROR_CODE_5,
    ERROR_CODE_6,
    ERROR_CODE_7,
    ERROR_CODE_8,
    ERROR_CODE_9,
    ERROR_CODE_10,
    ERROR_CODE_11,
    ERROR_CODE_12,
    ERROR_CODE_13,
    ERROR_CODE_14,
    ERROR_CODE_15,
    ERROR_CODE_16,
    ERROR_CODE_17,

    // Line-related errors
    ERROR_CODE_30 = 30,
    ERROR_CODE_31,
    ERROR_CODE_32,
    ERROR_CODE_33,
    ERROR_CODE_34,
    ERROR_CODE_35,
    ERROR_CODE_36,
    ERROR_CODE_37,
    ERROR_CODE_38,
    ERROR_CODE_39,
    ERROR_CODE_40,
    ERROR_CODE_41,
    ERROR_CODE_42,
    ERROR_CODE_43,
    ERROR_CODE_44,
    ERROR_CODE_45,
    ERROR_CODE_46,
    ERROR_CODE_47,

    // Instruction and data-related
    ERROR_CODE_50 = 50,
    ERROR_CODE_51,
    ERROR_CODE_52,
    ERROR_CODE_53,
    ERROR_CODE_54,
    ERROR_CODE_55,
    ERROR_CODE_56,
    ERROR_CODE_57,
    ERROR_CODE_58,
    ERROR_CODE_59
} ERROR_CODES;

/**
 * Prints a generic internal error to stderr.
 */
void print_internal_error(int code);

/**
 * Prints a file-position-aware external error to stdout.
 */
void print_external_error(int code, location loc);

/**
 * Closes/free multiple resources in case of a fatal error.
 * @param arg_count Number of arguments
 * @param type Either "file" or any other (treated as memory)
 */
void abrupt_close(int arg_count, const char *type, ...);

#endif
