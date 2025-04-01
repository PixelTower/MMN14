#ifndef FIRSTPASS_H
#define FIRSTPASS_H

// Include necessary headers
#include <stdio.h>

// Declare constants, if any
#define MAX_LABEL_LENGTH 31

// Declare types, if any
typedef struct {
    char label[MAX_LABEL_LENGTH];
    int address;
    int isExternal;
} Symbol;

// Declare functions
void firstPass(FILE *sourceFile);
int processLine(const char *line, int lineNumber);
int addSymbol(const char *label, int address, int isExternal);

#endif // FIRSTPASS_H