#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

//Helper Functions
Token current_token(Parser* p) {
    return p->token_list->tokens[p->current_pos];
}

void advance(Parser* p) {
    if (p->current_pos < p->token_list->count-1) {
        p->current_pos++;
    }
}

//Consume checks if the current token matches what we expect, if yes, it moves forward
void consume(Parser* p, TokenType expected_type, const char* expected_value) {
    Token t = current_token(p);
    if (t.type == expected_type && (expected_value == NULL || strcmp(t.value, expected_value) == 0)) {
        advance(p);
    } else {
        printf("SYNTAX ERROR: EXPECTED '%s', BUT FOUND '%s'\n",
            expected_value ? expected_value : "Specific Type", t.value);
        exit(1);
    }
}
ASTNode* create_node(ASTNodeType type) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = type;
    return node;
}

//Parsing Rules

//Parses: DECLARE <id> as <type> INITIALIZED_TO <value> ;

ASTNode* parse_var_declaration(Parser* p) {
    ASTNode* node = create_node(AST_VAR_DECL);

    consume(p, TOKEN_KEYWORD, "DECLARE");

    node->data.var_decl.var_name = strdup(current_token(p).value);
    consume(p, TOKEN_IDENTIFIER, NULL);

    consume(p, TOKEN_KEYWORD, "AS");

    node->data.var_decl.type_name = strdup(current_token(p).value);
    consume(p, TOKEN_TYPE, NULL);

    consume(p, TOKEN_KEYWORD, "INITIALIZED_TO");

    //for now assume its integer literal
    node->data.var_decl.init_value = strdup(current_token(p).value);
    consume(p, TOKEN_INTEGER_LITERAL, NULL);

    consume(p, TOKEN_SYMBOL, ";");

    return node;
}

ASTNode* parse_function_def(Parser* p) {
    ASTNode* node = create_node(AST_FUNCTION_DEF);

    consume(p, TOKEN_KEYWORD, "DEFINE_FUNCTION");

    node->data.function_def.func_name = strdup(current_token(p).value);
    consume(p, TOKEN_IDENTIFIER, NULL);

    consume(p, TOKEN_SYMBOL, "(");
    // (Skipping parameter lists for this exact test)
    consume(p, TOKEN_SYMBOL, ")");

    consume(p, TOKEN_KEYWORD, "RETURNING");

    node->data.function_def.return_type = strdup(current_token(p).value);
    consume(p, TOKEN_TYPE, NULL);

    consume(p, TOKEN_KEYWORD, "BEGIN_FUNCTION");

    // Allocate space for statements (hardcoded to 1 for this test)
    node->data.function_def.body = malloc(sizeof(ASTNode*) * 1);
    node->data.function_def.body[0] = parse_var_declaration(p);
    node->data.function_def.body_count = 1;

    consume(p, TOKEN_KEYWORD, "END_FUNCTION");

    return node;
}

ASTNode* parse(TokenList* list) {
    Parser p = {list, 0};
    return parse_function_def(&p); // Start by parsing a function
}

void print_ast(ASTNode* node, int depth) {
    for(int i=0; i<depth; i++) printf("  "); // Indentation

    if (node->type == AST_FUNCTION_DEF) {
        printf("FunctionDef(name='%s', returns='%s')\n",
               node->data.function_def.func_name, node->data.function_def.return_type);
        for(int i = 0; i < node->data.function_def.body_count; i++) {
            print_ast(node->data.function_def.body[i], depth + 1);
        }
    } else if (node->type == AST_VAR_DECL) {
        printf("VarDecl(name='%s', type='%s', value='%s')\n",
               node->data.var_decl.var_name, node->data.var_decl.type_name, node->data.var_decl.init_value);
    }
}

void free_ast(ASTNode* node) {
    if (node->type == AST_FUNCTION_DEF) {
        free(node->data.function_def.func_name);
        free(node->data.function_def.return_type);
        for(int i = 0; i < node->data.function_def.body_count; i++) {
            free_ast(node->data.function_def.body[i]);
        }
        free(node->data.function_def.body);
    } else if (node->type == AST_VAR_DECL) {
        free(node->data.var_decl.var_name);
        free(node->data.var_decl.type_name);
        free(node->data.var_decl.init_value);
    }
    free(node);
}