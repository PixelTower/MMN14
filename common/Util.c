#include "util.h"

/* Allocates memory and exits if allocation fails*/
void *handle_malloc(size_t size) {
    void *ptr = malloc(size);
    if (!ptr) {
        fprintf(stderr, "[ERROR] Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

/* Creates a new string by appending a new file extension to a base filename*/
char *add_new_file(const char *base_name, const char *new_extension) {
    size_t len = strlen(base_name) + strlen(new_extension) + 2; 
    char *new_file = (char *)handle_malloc(len);
    strcpy(new_file, base_name); /* Copy base filename */
    strcat(new_file, new_extension); 
    return new_file;
}

/* Encodes a 12-bit short value into 2-character base64 representation*/
char *short_to_base64(unsigned short value) {
    static const char base64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    char *encoded = (char *)handle_malloc(3); 
    encoded[0] = base64_chars[(value >> 6) & 0x3F]; 
    encoded[1] = base64_chars[value & 0x3F];        
    encoded[2] = '\0';
    return encoded;
}
