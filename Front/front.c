#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "front.h"
#include "prepro.h"
#include "data_strct.h"
#include "util.h"
#include "Errors.h"
#include "handle_text.h"
#include "firstpass.h"
#include "secondpass.h"
#include "backend.h"
#include "globals.h"
#include "lexer.h"

/* AST helpers (נשאר בדיוק כמו שהיה בפרויקט שלך) */
void build_ast_from_file(node *head);
void print_macro_tree(node *ast);
void free_macro_list(node *head);
void free_instruction_ast();

/* AST root pointer from your AST module */
extern ASTNode *inst_ast;

/* Debug toggle */
#define DEBUG_MODE 1

/* Function declarations */
int count_ast_instructions(ASTNode *head);
int count_macros(node *head);

int main(int argc, char *argv[]) {
    int i;
    int success_counter = 0;
    int total_errors = 0;
    int total_macros = 0;
    int total_instructions = 0;

    if (argc < 2) {
        print_internal_error(ERROR_CODE_2);
        return EXIT_FAILURE;
    }

    printf("\nAssembler started for %d file(s)\n\n", argc - 1);

    for (i = 1; i < argc; i++) {
        char *file_name = argv[i];
        char *as_file = NULL;
        char *clean_file = NULL;
        char *am_file = NULL;

        int label_lines = 0, extern_lines = 0, entries_lines = 0;
        int has_error = 0;
        int instruction_count = 0;

        node *macro_list = NULL;
        label_struct *label_table = NULL;

        printf("===== Processing file: %s =====\n", file_name);

        /* Step 1: build .as file name and clean it */
        as_file = add_new_file(file_name, ".as");
        clean_file = remove_extra_spaces_file(as_file);
        if (!clean_file) {
            printf("Error: cleaning failed for %s\n", as_file);
            free(as_file);
            total_errors++;
            continue;
        }

        /* Step 2: preprocess macros */
        macro_list = mcro_exec(clean_file);
        if (!macro_list) {
            printf("Error: macro preprocessing failed\n");
            free(as_file);
            free(clean_file);
            total_errors++;
            continue;
        }

        /* Step 3: build AST and print */
        build_ast_from_file(macro_list);
        print_macro_tree(macro_list);

        total_macros += count_macros(macro_list);
        instruction_count = count_ast_instructions(inst_ast);
        total_instructions += instruction_count;

        if (DEBUG_MODE) {
            printf("[DEBUG] Instructions in AST: %d\n", instruction_count);
        }

        /* Step 4: create .am file name */
        am_file = add_new_file(file_name, ".am");
        if (!am_file) {
            printf("Error: failed to create .am file\n");
            free_macro_list(macro_list);
            free(as_file);
            free(clean_file);
            total_errors++;
            continue;
        }

        /* Step 5: First Pass */
        label_table = exe_first_pass(am_file, &label_lines, &has_error);
        if (!label_table || has_error) {
            printf("Error: first pass failed\n");
            free_macro_list(macro_list);
            free(as_file);
            free(clean_file);
            free(am_file);
            total_errors++;
            continue;
        }

        if (DEBUG_MODE) {
            printf("[DEBUG] First pass complete. Labels: %d\n", label_lines);
        }

        /* Step 6: Second Pass */
        exe_second_pass(file_name, label_table, label_lines, &has_error, &extern_lines, &entries_lines);
        if (has_error) {
            printf("Error: second pass failed\n");
            free_label_table(label_table, label_lines);
            free_macro_list(macro_list);
            free_instruction_ast();
            free(as_file);
            free(clean_file);
            free(am_file);
            total_errors++;
            continue;
        }

        /* Per-file summary */
        printf("✅ %s processed successfully.\n", file_name);
        printf("- Instructions: %d\n", instruction_count);
        printf("- Macros: %d\n", count_macros(macro_list));
        if (extern_lines > 0) printf("- Externs: %d\n", extern_lines);
        if (entries_lines > 0) printf("- Entries: %d\n", entries_lines);
        printf("- Output: %s.ob", file_name);
        if (extern_lines > 0) printf(", %s.ext", file_name);
        if (entries_lines > 0) printf(", %s.ent", file_name);
        printf("\n\n");

        /* Cleanup */
        free_label_table(label_table, label_lines);
        free_macro_list(macro_list);
        free_instruction_ast();
        free(as_file);
        free(clean_file);
        free(am_file);

        success_counter++;
    }

    /* Global summary */
    printf("===== Assembly Finished =====\n");
    printf("Files assembled: %d\n", success_counter);
    printf("Errors found: %d\n", total_errors);
    printf("Total macros: %d\n", total_macros);
    printf("Total instructions: %d\n", total_instructions);
    printf("=============================\n");

    return 0;
}

/* Count the number of instructions in the AST */
int count_ast_instructions(ASTNode *head) {
    int count = 0;
    while (head != NULL) {
        if (what_opcode(head->opcode) >= 0 || is_instr(head->opcode)) {
            count++;
        }
        head = head->next;
    }
    return count;
}

/* Count number of macros in macro list */
int count_macros(node *head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}
