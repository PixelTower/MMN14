/* data_strct.c - Implements linked list functions for macro storage */

#include "data_strct.h"

/* Creates a new macro node with name, content, and line number */
node *make_node(const char *name, const char *content, int line_num) {
    node *new_node = (node *)malloc(sizeof(node));
    if (!new_node) {
        fprintf(stderr, "[ERROR] Failed to allocate memory for macro node.\n");
        return NULL;
    }

    new_node->name = strdup(name);
    new_node->content = strdup(content);
    new_node->line = line_num;
    new_node->next = NULL;

    return new_node;
}

/* Adds a macro node to the end of the list */
void add_to_list(node **head, const char *name, const char *content, int line_num) {
    node *new_node = make_node(name, content, line_num);
    if (!new_node) return;

    if (*head == NULL) {
        *head = new_node;
    } else {
        node *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

/* Frees all memory used by the macro list */
void free_macro_list(node *head) {
    node *temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp->name);
        free(temp->content);
        free(temp);
    }
}

/* Searches for a macro by name and returns it. Sets found = 1 if found */
node *search_list(node *head, const char *name, int *found) {
    while (head) {
        if (strcmp(head->name, name) == 0) {
            *found = 1;
            return head;
        }
        head = head->next;
    }
    *found = 0;
    return NULL;
}