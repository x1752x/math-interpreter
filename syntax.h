#ifndef SYNTAX_H
#define SYNTAX_H

typedef enum {
    DIGIT,
    PREFIX_FUNCTION,
    LBRACKET,
    RBRACKET,
    BINAR_OPERATION
} Syntax;

void push(Lexem lexem, Lexem** array, size_t* size);

Lexem pop(Lexem** array, size_t* size);

int get_syntax(Lexem lexem);

int get_priority(Lexem lexem);

Lexem* to_RPN(Lexem* lexems);

#endif