/* filepath: /Users/ohadrahum/Documents/GettingStarted/MMN14/Front/front.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "preproc.h"
#include "first_pass.h"
#include "second_pass.h"


#define MAX_LINE_LENGTH 256
#define MAX_LABEL_LENGTH 31
#define MAX_OPCODE_LENGTH 10
#define MAX_OPERAND_LENGTH 128

// Structure representing a single line of assembly in AST form
typedef struct ASTNode {
    char label[MAX_LABEL_LENGTH];
    char opcode[MAX_OPCODE_LENGTH];
    char operand1[MAX_OPERAND_LENGTH];
    char operand2[MAX_OPERAND_LENGTH];
    int line_number;
    struct ASTNode *next;
} ASTNode;

// Parse a line of assembly into an ASTNode
ASTNode *create_ast_node(const char *line, int line_number) {
    ASTNode *node;
    char temp[MAX_LINE_LENGTH], *token;
    int token_count = 0;

    printf("[DEBUG] Creating AST node from line %d: %s", line_number, line);

    node = (ASTNode *)malloc(sizeof(ASTNode));
    if (!node) {
        printf("[ERROR] Memory allocation failed for ASTNode at line %d\n", line_number);
        return NULL;
    }

    // Initialize all fields
    node->label[0] = '\0';
    node->opcode[0] = '\0';
    node->operand1[0] = '\0';
    node->operand2[0] = '\0';
    node->line_number = line_number;
    node->next = NULL;

    strncpy(temp, line, MAX_LINE_LENGTH - 1);
    temp[MAX_LINE_LENGTH - 1] = '\0';
    token = strtok(temp, " \t,");

    // Parse up to four tokens: label (if exists), opcode, operand1, operand2
    while (token && token_count < 4) {
        if (token_count == 0 && strchr(token, ':')) {
            strncpy(node->label, token, MAX_LABEL_LENGTH - 1);
            node->label[MAX_LABEL_LENGTH - 1] = '\0';
            size_t len = strlen(node->label);
            if (len > 0 && node->label[len - 1] == ':') {
                node->label[len - 1] = '\0';
            }
        } else if (node->opcode[0] == '\0') {
            strncpy(node->opcode, token, MAX_OPCODE_LENGTH - 1);
            node->opcode[MAX_OPCODE_LENGTH - 1] = '\0';
        } else if (node->operand1[0] == '\0') {
            strncpy(node->operand1, token, MAX_OPERAND_LENGTH - 1);
            node->operand1[MAX_OPERAND_LENGTH - 1] = '\0';
        } else {
            strncpy(node->operand2, token, MAX_OPERAND_LENGTH - 1);
            node->operand2[MAX_OPERAND_LENGTH - 1] = '\0';
        }
        token = strtok(NULL, " \t,");
        token_count++;
    }

    return node;
}

// Build the full AST from a file line by line
ASTNode *build_ast_from_file(const char *file_name) {
    FILE *fp;
    char line[MAX_LINE_LENGTH];
    int line_num = 0;
    ASTNode *head = NULL, *tail = NULL;

    printf("[DEBUG] Opening file for AST build: %s\n", file_name);
    fp = fopen(file_name, "r");
    if (!fp) {
        printf("[ERROR] Failed to open file: %s\n", file_name);
        return NULL;
    }

    while (fgets(line, sizeof(line), fp)) {
        ASTNode *node;
        line_num++;

        // Skip empty lines and comments
        if (line[0] == ';' || line[0] == '\n') continue;

        node = create_ast_node(line, line_num);
        if (!node) continue;

        // Append node to linked list
        if (!head) {
            head = tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }

    fclose(fp);
    return head;
}

// Print the macro definitions tree
void print_macro_tree(node *head) {
    printf("[DEBUG] Printing macro tree\n");
    while (head != NULL) {
        printf("Macro: %s (defined at line %d)\n", head->name, head->line);
        head = head->next;
    }
}

// Print the parsed instructions from the AST
void print_instruction_ast(ASTNode *head) {
    printf("\n--- Instruction AST (Filtered) ---\n");
    while (head) {
        if (what_opcode(head->opcode) >= 0 || is_instr(head->opcode)) {
            printf("Line %d:\n", head->line_number);
            if (head->label[0]) printf("  Label: %s\n", head->label);
            printf("  Opcode: %s\n", head->opcode);
            if (head->operand1[0]) printf("  Operand1: %s\n", head->operand1);
            if (head->operand2[0]) printf("  Operand2: %s\n", head->operand2);
        }
        head = head->next;
    }
    printf("----------------------------------\n");
}

// Free memory allocated to AST
void free_instruction_ast(ASTNode *head) {
    ASTNode *tmp;
    printf("[DEBUG] Freeing instruction AST\n");
    while (head) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

// Main program logic
int main(int argc, char *argv[]) {
    char *as_file = NULL, *am_file = NULL;
    node *ast = NULL;
    ASTNode *inst_ast = NULL;
    int i;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file1> <file2> ...\n", argv[0]);
        return 1;
    }

    for (i = 1; i < argc; i++) {
        printf("[INFO] Processing file: %s\n", argv[i]);

        // Create .as file name
        as_file = add_new_file(argv[i], ".as");
        if (!as_file) continue;

        // Run macro preprocessor
        printf("[INFO] Running preprocessor on: %s\n", as_file);
        if (!mcro_exec(as_file, &ast)) {
            printf("[ERROR] Preprocessor failed for: %s\n", as_file);
            free(as_file);
            continue;
        }

        // Create .am file name
        am_file = add_new_file(argv[i], ".am");
        if (!am_file) {
            free(as_file);
            continue;
        }

        // Run first pass
        printf("[INFO] Running first pass on: %s\n", am_file);
        if (exe_first_pass(am_file) != 0) {
            printf("[ERROR] First pass failed for: %s\n", am_file);
            free(as_file);
            free(am_file);
            continue;
        }

        // Build and print instruction AST for debugging
        inst_ast = build_ast_from_file(am_file);
        if (inst_ast) {
            print_instruction_ast(inst_ast);
            free_instruction_ast(inst_ast);
        }

        // Run second pass
        printf("[INFO] Running second pass on: %s\n", am_file);
        if (exe_second_pass(am_file) != 0) {
            fprintf(stderr, "Second pass failed for %s\n", am_file);
        }

        free(as_file);
        free(am_file);
    }

    // Print and free macro AST
    print_macro_tree(ast);
    free_macro_list(ast);

    return 0;
}
