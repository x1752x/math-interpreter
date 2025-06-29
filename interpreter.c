#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include "lexem.h"
#include "syntax.h"

typedef enum {
    OPERAND,
    OPERATOR
} Role;

int get_role(Lexem lexem) {
    switch (get_syntax(lexem)) {
        case PREFIX_FUNCTION: return OPERATOR;
        case BINAR_OPERATION: return OPERATOR;
        case DIGIT: return OPERAND;
        default: return -1;
    }
}

double interpret(Lexem* RPN) {
    size_t RPN_size = malloc_usable_size(RPN) / sizeof(Lexem);

    Lexem* stack = NULL;
    size_t stack_size = 0;

    for (int i = 0; i < RPN_size; i++) {
        if (get_role(RPN[i]) == OPERAND) {
            push(RPN[i], &stack, &stack_size);
            continue;
        }

        if (get_role(RPN[i]) == OPERATOR) {
            switch (RPN[i].type) {
                case LEXEM_ADD: {
                    double b = atof(pop(&stack, &stack_size).value);
                    double a = atof(pop(&stack, &stack_size).value);
                    Lexem result = {LEXEM_FLOAT, malloc(32)};
                    sprintf(result.value, "%f", a + b);
                    push(result, &stack, &stack_size);
                    continue;
                }
                case LEXEM_SUB: {
                    double b = atof(pop(&stack, &stack_size).value);
                    double a = atof(pop(&stack, &stack_size).value);
                    Lexem result = {LEXEM_FLOAT, malloc(32)};
                    sprintf(result.value, "%f", a - b);
                    push(result, &stack, &stack_size);
                    continue;
                }
                case LEXEM_MUL: {
                    double b = atof(pop(&stack, &stack_size).value);
                    double a = atof(pop(&stack, &stack_size).value);
                    Lexem result = {LEXEM_FLOAT, malloc(32)};
                    sprintf(result.value, "%f", a * b);
                    push(result, &stack, &stack_size);
                    continue;
                }
                case LEXEM_DIV: {
                    double b = atof(pop(&stack, &stack_size).value);
                    double a = atof(pop(&stack, &stack_size).value);
                    Lexem result = {LEXEM_FLOAT, malloc(32)};
                    sprintf(result.value, "%f", a / b);
                    push(result, &stack, &stack_size);
                    continue;
                }
                case LEXEM_POW: {
                    double b = atof(pop(&stack, &stack_size).value);
                    double a = atof(pop(&stack, &stack_size).value);
                    Lexem result = {LEXEM_FLOAT, malloc(32)};
                    sprintf(result.value, "%f", pow(a, b));
                    push(result, &stack, &stack_size);
                    continue;
                }
                case LEXEM_SQRT: {
                    double x = atof(pop(&stack, &stack_size).value);
                    Lexem result = {LEXEM_FLOAT, malloc(32)};
                    sprintf(result.value, "%f", sqrt(x));
                    push(result, &stack, &stack_size);
                    continue;
                }
                default: {
                    continue;
                }
            }
        }
    }

    return atof(pop(&stack, &stack_size).value);
}