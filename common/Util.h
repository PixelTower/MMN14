#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Allocates memory and checks for success */
void *handle_malloc(size_t size);

/* Creates a new filename with a different extension */
char *add_new_file(const char *base_name, const char *new_extension);

/* Converts short number to base64 encoded string */
char *short_to_base64(unsigned short value);

#endif
