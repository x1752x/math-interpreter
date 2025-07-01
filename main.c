#define PLAYGROUND 0
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <setjmp.h>
#include <ctype.h>
#include "lexem.h"
#include "syntax.h"
#include "interpreter.h"

void loop() {
    while (1) {
        char* line = NULL;
        size_t length = 0;
        printf(">>> ");
        if (getline(&line, &length, stdin) == -1) {
            fprintf(stderr, "\nCould not read input\n");
            exit(1);
        }

        while(isspace(*line)) line++;
        if (*line == '\0') continue;

        Lexem* lexems;
        Lexem* RPN;
        double value;

        lexems = parse_lexems(&line);
        RPN = to_RPN(lexems);
        value = interpret(RPN);

        printf("%f\n", value);
    }
}

int main() {
    #if !PLAYGROUND
        loop();
        return 0;
    #endif

    char* test_string = "3 + 4 * 2 / (1 - 5)^2";

    printf("Test string: %s\n\n", test_string);
    
    Lexem* lexems = parse_lexems(&test_string);
    size_t lexems_number = malloc_usable_size(lexems) / sizeof(Lexem);

    printf("Testing lexer...\n\n");

    for (int i = 0; i < lexems_number; i++) {
        printf("%d | %s\n", lexems[i].type, lexems[i].value);
    }

    printf("\nTesting parser...\n\n");

    Lexem* RPN = to_RPN(lexems);
    size_t RPN_size = malloc_usable_size(RPN) / sizeof(Lexem);

    for (int i = 0; i < RPN_size; i++) {
        printf("%d | %s\n", RPN[i].type, RPN[i].value);
    }

    printf("\nTesting interpreter...\n\n");

    printf("%f\n", interpret(RPN));

    return 0;
}