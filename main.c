#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

int main(){

    char source_code[] =
        "DEFINE_FUNCTION main ( ) RETURNING VOID \n"
        "BEGIN_FUNCTION \n"
        "DECLARE x AS INTEGER INITIALIZED_TO 5 ; \n"
        "END_FUNCTION";

    printf("Starting compilation process... \n\n");

    //Lexical analysis
    TokenList tokens = lex(source_code);

    //print results to verify it worked
    print_tokens(&tokens);

    //cleanup memory
    free_token_list(&tokens);

    return 0;
}