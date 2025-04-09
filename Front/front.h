#ifndef FRONT_H
#define FRONT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
   Include any other project-specific headers that define
   the types and functions you use in front.c.
*/
#include "prepro.h"
#include "data_strct.h"
#include "Util.h"
#include "Errors.h"
#include "handle_text.h"
#include "firstpass.h"
#include "secondpass.h"
#include "backend.h"
#include "globals.h"
#include "lexer.h"

void build_ast_from_file(node *head);
void print_macro_tree(node *head);
void free_macro_list(node *head);
void free_instruction_ast(void);
int count_ast_instructions(ASTNode *head);
int count_macros(node *head);

#endif /* FRONT_H */
