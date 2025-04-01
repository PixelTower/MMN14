#ifndef PREPRO_H
#define PREPRO_H

#include "data_strct.h" /* For node struct */

/* 
 * Reads a .as file, extracts macros (mcro ... endmcro),
 * stores them in a linked list,
 * replaces macro calls with their body,
 * and writes the output to a new .am file.
 * Returns the macro list (can be used later for printing or freeing).
 */
node *mcro_exec(const char *file_name);

#endif
