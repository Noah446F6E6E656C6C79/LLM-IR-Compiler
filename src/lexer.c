#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

//Dynamic array implementation
void init_token_list(TokenList* list) {
    list->capacity = 100;
    list->count = 0;
    list->tokens = malloc(list->capacity*sizeof(Token));
}

void add_token(TokenList* list, TokenType type, const char* value) {
    if (list->count >= list->capacity) {
        list->capacity*=2;
        list->tokens = realloc(list->tokens, list->capacity*sizeof(Token));
    }
    list->tokens[list->count].type = type;
    list->tokens[list->count].value = strdup(value); //duplicate the string into safe memory
    list->count++;
}

void free_token_list(TokenList* list) {
    for (int i=0; i<list->count; i++) {
        free(list->tokens[i].value); //free duplicated strings
    }
    free(list->tokens); //free the array itsself
}

//Helper for keywords

bool is_keyword(const char* word) {
    const char* keywords[] = {
        "DEFINE_FUNCTION", "RETURNING", "BEGIN_FUNCTION", "END_FUNCTION",
        "DECLARE", "AS", "INITIALIZED_TO", "SET", "TO", "IF", "THEN", "ELSE",
        "END_IF", "WHILE", "DO", "END_WHILE", "RETURN", "CALL",
        "IS_EQUAL_TO", "IS_NOT_EQUAL_TO", "PLUS", "MINUS" // Add the rest later
    };

    int num_keywords = sizeof(keywords)/sizeof(keywords[0]);
    for (int i=0; i<num_keywords; i++) {
        if (strcmp(word, keywords[i])==0) return true;
    }
    return false;
}

//The Lexer
TokenList lex(char* source_code) {
    TokenList list;
    init_token_list(&list);

    //break string by spaces, tabs, and newlines
    char* word = strtok(source_code, " \t\n\r");
    while (word != NULL) {
        if (is_keyword(word)) {
            add_token(&list, TOKEN_KEYWORD, word);
        } else if (strcmp(word, "INTEGER") == 0 || strcmp(word, "BOOLEAN") == 0 ||
                   strcmp(word, "STRING") == 0 || strcmp(word, "VOID") == 0) {
            add_token(&list, TOKEN_TYPE, word);
        } else if (strcmp(word, "TRUE") == 0 || strcmp(word, "FALSE") == 0) {
            add_token(&list, TOKEN_BOOLEAN_LITERAL, word);
        } else if (strcmp(word, "(") == 0 || strcmp(word, ")") == 0 ||
                   strcmp(word, ";") == 0 || strcmp(word, ",") == 0) {
            add_token(&list, TOKEN_SYMBOL, word);
        } else if (isdigit(word[0]) || (word[0] == '-' && isdigit(word[1]))) {
            add_token(&list, TOKEN_INTEGER_LITERAL, word);
        } else if (word[0] == '"') {
            // Note: This simple version assumes strings have no spaces inside them.
            add_token(&list, TOKEN_STRING_LITERAL, word);
        } else {
            add_token(&list, TOKEN_IDENTIFIER, word);
        }

        word = strtok(NULL, " \t\n");
    }
    add_token(&list, TOKEN_EOF, "EOF");
    return list;
}

//debugging tool
void print_tokens(TokenList* list) {
    const char* type_names[] = {
        "KEYWORD", "TYPE", "SYMBOL", "IDENTIFIER",
        "INT_LIT", "STR_LIT", "BOOL_LIT", "EOF"
    };

    printf("--- Token Stream ---\n");
    for (int i = 0; i < list->count; i++) {
        printf("[%s] : '%s'\n", type_names[list->tokens[i].type], list->tokens[i].value);
    }
    printf("--------------------\n");
}