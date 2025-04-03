#ifndef SECONDPASS_H
#define SECONDPASS_H

/* Include necessary headers*/
#include <stdio.h>

/* Declare functions from secondpass.c*/
void performSecondPass(const char *filename);
int validateSecondPassData();
void handleSecondPassError(const char *errorMessage);

#endif 