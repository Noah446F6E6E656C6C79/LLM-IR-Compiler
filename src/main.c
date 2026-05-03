#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"

// A robust function to read an entire file into memory
char* read_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("ERROR: Could not open file '%s'\n", filename);
        return NULL;
    }

    // Jump to the end of the file to find out how many bytes it is
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET); // Jump back to the beginning

    // Allocate memory for the file contents + 1 byte for the null terminator
    char* buffer = malloc(length + 1);
    if (buffer == NULL) {
        printf("ERROR: Memory allocation failed\n");
        fclose(file);
        return NULL;
    }

    // Read the file into the buffer and null-terminate it
    fread(buffer, 1, length, file);
    buffer[length] = '\0';

    fclose(file);
    return buffer;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: compiler <filename.txt>\n");
        return 1;
    }

    char* source_code = read_file(argv[1]);
    if (source_code == NULL) {
        return 1;
    }

    // --- THE BOM FIX ---
    // If Windows hid a 3-byte BOM at the start of the file, skip past it.
    char* code_start = source_code;
    if ((unsigned char)code_start[0] == 0xEF &&
        (unsigned char)code_start[1] == 0xBB &&
        (unsigned char)code_start[2] == 0xBF) {
        code_start += 3; // Shift the starting point forward 3 bytes
        }

    printf("Compiling %s...\n\n", argv[1]);

    // Notice we pass 'code_start' to the lexer instead of 'source_code' now
    TokenList tokens = lex(code_start);
    ASTNode* root = parse(&tokens);

    printf("--- Abstract Syntax Tree ---\n");
    print_ast(root, 0);

    free_ast(root);
    free_token_list(&tokens);
    free(source_code); // We still free the original pointer to avoid memory leaks

    printf("\nCompilation successful!\n");
    return 0;
}