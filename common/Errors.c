#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "util.h"
#include "Errors.h" 

/* Define an array of error structures with code and message*/
Error errors[] = {
    {ERROR_CODE_0,  "No Error"},
    {ERROR_CODE_1,  "Failed to dynamically allocate memory"},
    {ERROR_CODE_2,  ".as files name is missing"},
    {ERROR_CODE_3,  "The file name is too long"},
    {ERROR_CODE_4,  "The provided file name does not exist"},
    {ERROR_CODE_5,  ".am file is missing"},
    {ERROR_CODE_6,  "The line is too long"},
    {ERROR_CODE_7,  "Failed to open new file for writing"},
    {ERROR_CODE_8,  "Failed to open file for reading"},
    {ERROR_CODE_9,  "Macro without name definition"},
    {ERROR_CODE_10, "Extra text after macro name definition"},
    {ERROR_CODE_11, "Setting a position in a file failed"},
    {ERROR_CODE_12, "endmcro with extra text"},
    {ERROR_CODE_13, "Macro has more than one definition"},
    {ERROR_CODE_14, "Failed to copy file during macro expansion"},
    {ERROR_CODE_15, "Macro expansion in .as file failed"},
    {ERROR_CODE_16, "Macro call before declaration"},
    {ERROR_CODE_17, "Illegal name for a macro"},
    {ERROR_CODE_30, "Line is too long"},
    {ERROR_CODE_31, "Illegal opcode"},
    {ERROR_CODE_32, "Line contains extra text"},
    {ERROR_CODE_33, "Illegal argument"},
    {ERROR_CODE_34, "Missing argument"},
    {ERROR_CODE_35, "Missing comma between arguments"},
    {ERROR_CODE_36, "Label not defined in the assembly file"},
    {ERROR_CODE_37, "Illegal label after .entry"},
    {ERROR_CODE_38, "Illegal comma near opcode"},
    {ERROR_CODE_39, "More commas than needed"},
    {ERROR_CODE_40, "Comma in the wrong place"},
    {ERROR_CODE_41, "Illegal character near opcode or label"},
    {ERROR_CODE_42, "Illegal character"},
    {ERROR_CODE_43, "Missing comma between numbers"},
    {ERROR_CODE_44, "Illegal label declaration"},
    {ERROR_CODE_45, "Missing ':' after label declaration"},
    {ERROR_CODE_46, "Illegal register name. Use only @r1-@r7"},
    {ERROR_CODE_47, "Illegal comma before opcode"},
    {-1, ""} 
};

/* Prints internal error message based on the given error code*/
void print_internal_error(int code) {
    int i;
    for (i = 0; errors[i].error_id != -1; i++) {
        if (errors[i].error_id == code) {
            fprintf(stderr, "[INTERNAL ERROR %d] %s\n", code, errors[i].error_msg);
            return;
        }
    }
    fprintf(stderr, "[INTERNAL ERROR %d] Unknown error.\n", code);
}

/* Prints external error message including the file and line number where it occurred*/
void print_external_error(int code, location loc) {
    int i;
    for (i = 0; errors[i].error_id != -1; i++) {
        if (errors[i].error_id == code) {
            printf("%s:%d: error: %s\n", loc.file_name, loc.line_num, errors[i].error_msg);
            return;
        }
    }
    printf("%s:%d: error: Unknown error (%d)\n", loc.file_name, loc.line_num, code);
}

/* Utility function to close multiple files or free multiple pointers on fatal errors*/
void abrupt_close(int arg_count, const char *type, ...) {
    int i;
    va_list args;
    void *ptr;

    va_start(args, type);
    for (i = 0; i < arg_count; i++) {
        ptr = va_arg(args, void *);
        if (strcmp(type, "file") == 0) {
            fclose((FILE *)ptr);
        } else {
            free(ptr);
        }
    }
    va_end(args);
}
