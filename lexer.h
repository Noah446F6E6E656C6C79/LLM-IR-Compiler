#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>

//all possible token types
typedef enum {
    TOKEN_KEYWORD,
     TOKEN_TYPE,
     TOKEN_SYMBOL,
     TOKEN_IDENTIFIER,
     TOKEN_INTEGER_LITERAL,
     TOKEN_STRING_LITERAL,
     TOKEN_BOOLEAN_LITERAL,
     TOKEN_EOF
} TokenType;

//Token structure
typedef struct {
  TokenType type;
  char* value;
} Token;

//Dynamic array for tokens
typedef struct {
  Token* tokens;
  int capacity;
  int count;
} TokenList;

//function prototypes
void init_token_list(TokenList* list);
void add_token(TokenList* list, TokenType type, const char* value);
void free_token_list(TokenList* list);
TokenList lex(char* source_code);
void print_tokens(TokenList* list);

#endif