#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

// 1. Define the types of nodes in our tree
typedef enum {
    AST_FUNCTION_DEF,
    AST_VAR_DECL
} ASTNodeType;

// 2. The Node Structure
typedef struct ASTNode {
    ASTNodeType type;

    union {
        // Data for a Function Definition
        struct {
            char* func_name;
            char* return_type;
            struct ASTNode** body; // Dynamic array of statement nodes inside the function
            int body_count;
        } function_def;

        // Data for a Variable Declaration
        struct {
            char* var_name;
            char* type_name;
            char* init_value; // We'll store the literal value as a string for now
        } var_decl;
    } data;
} ASTNode;

// 3. Parser State Structure
typedef struct {
    TokenList* token_list;
    int current_pos;
} Parser;

// 4. Function Prototypes
ASTNode* parse(TokenList* list);
void print_ast(ASTNode* node, int depth);
void free_ast(ASTNode* node);

#endif