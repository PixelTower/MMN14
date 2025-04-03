#ifndef ERRORS_H
#define ERRORS_H
#define ERROR_CODE_2 2
#define ERROR_CODE_7 7
#define ERROR_CODE_30 30


#include <stdio.h>

/* === Error location type === */
typedef enum {
    LOCATION_NONE,
    LOCATION_LINE,
    LOCATION_MACRO,
    LOCATION_MEMORY
} location;

/* === Error structure === */
typedef struct {
    int code;
    const char *message;
    location loc_type;
} Error;

/* === Function declarations === */

/*
 * Set the location type for where the error occurred.
 */
void set_location(location loc);

/*
 * Print an internal error from the predefined list.
 */
void print_internal_error(int code);

/*
 * Print a custom error with format and arguments.
 */
void print_error(const char *format, ...);

/*
 * Print a warning (non-fatal).
 */
void print_warning(const char *format, ...);

/*
 * Abruptly close execution and free resources.
 */
void abrupt_close(fp);

#endif
