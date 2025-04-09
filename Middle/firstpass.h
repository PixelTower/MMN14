#ifndef FIRSTPASS_H
#define FIRSTPASS_H

#include <stdio.h>

/* Declare constants, if any*/
#define MAX_LABEL_LENGTH 31

/* Declare types, if any*/
typedef struct
{
    char label[MAX_LABEL_LENGTH];
    int address;
    int isExternal;
} Symbol;

void first_pass(FILE *sourceFile);
/* (Removed declarations of processLine and addSymbol – not used) */

#endif
