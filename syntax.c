#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "lexem.h"

typedef enum {
    DIGIT,
    PREFIX_FUNCTION,
    LBRACKET,
    RBRACKET,
    BINAR_OPERATION
} Syntax;

void push(Lexem lexem, Lexem** array, size_t* size) {
    *array = (Lexem*)realloc(*array, (*size + 1) * sizeof(Lexem));
    (*array)[*size] = lexem;
    (*size)++;
}

Lexem pop(Lexem** array, size_t* size) {
    Lexem result = (*array)[*size - 1];
    *array = (Lexem*)realloc(*array, (*size - 1) * sizeof(Lexem));
    (*size)--;
    return result;
}

int get_syntax(Lexem lexem) {
    switch(lexem.type) {
        case LEXEM_INTEGER: return DIGIT;
        case LEXEM_FLOAT: return DIGIT;
        
        case LEXEM_SQRT: return PREFIX_FUNCTION;
        
        case LEXEM_LBRACKET: return LBRACKET;
        case LEXEM_RBRACKET: return RBRACKET;

        case LEXEM_ADD: return BINAR_OPERATION;
        case LEXEM_SUB: return BINAR_OPERATION;
        case LEXEM_MUL: return BINAR_OPERATION;
        case LEXEM_DIV: return BINAR_OPERATION;
        case LEXEM_POW: return BINAR_OPERATION;

        default: return -1;
    }
}

int get_priority(Lexem lexem) {
    switch (lexem.type) {
        case LEXEM_POW: {
            return 2;
        }
        case LEXEM_MUL: {
            return 1;
        }
        case LEXEM_DIV: {
            return 1;
        }
        case LEXEM_ADD: {
            return 0;
        }
        case LEXEM_SUB: {
            return 0;
        }
        default: {
            return -1;
        }
    }
}

Lexem* to_RPN(Lexem* lexems) {
    Lexem* RPN = NULL;
    size_t RPN_size = 0;

    Lexem* stack = NULL;
    size_t stack_size = 0;

    size_t lexems_number = malloc_usable_size(lexems) / sizeof(Lexem);


    for (int i = 0; i < lexems_number; i++) {
        if (get_syntax(lexems[i]) == DIGIT) {
            push(lexems[i], &RPN, &RPN_size);
            continue;
        }

        if (get_syntax(lexems[i]) == PREFIX_FUNCTION) {
            push(lexems[i], &stack, &stack_size);
            continue;
        }

        if (get_syntax(lexems[i]) == LBRACKET) {
            push(lexems[i], &stack, &stack_size);
            continue;
        }

        if (get_syntax(lexems[i]) == RBRACKET) {
            for (Lexem l = pop(&stack, &stack_size); l.type != LEXEM_LBRACKET; l = pop(&stack, &stack_size)) {
                push(l, &RPN, &RPN_size);
            }
            continue;
        }

        if (get_syntax(lexems[i]) == BINAR_OPERATION) {
            while (
                (stack_size > 0 && get_syntax(stack[stack_size - 1]) == PREFIX_FUNCTION) ||
                (stack_size > 0 && get_priority(stack[stack_size - 1]) >= get_priority(lexems[i]))
            ) {
                push(pop(&stack, &stack_size), &RPN, &RPN_size);
            }
            push(lexems[i], &stack, &stack_size);
        }
    }

    while (stack_size > 0) {
        push(pop(&stack, &stack_size), &RPN, &RPN_size);
    }

    return RPN;
}