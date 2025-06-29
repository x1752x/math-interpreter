#ifndef LEXEM_H
#define LEXEM_H

typedef enum {
    LEXEM_INTEGER,
    LEXEM_FLOAT,
    LEXEM_ADD,
    LEXEM_SUB,
    LEXEM_MUL,
    LEXEM_DIV,
    LEXEM_POW,
    LEXEM_SQRT,
    LEXEM_LBRACKET,
    LEXEM_RBRACKET,
    LEXEM_EOF,
    LEXEM_UNKNOWN
} LexemType;

typedef struct {
    LexemType type;
    char* value;
} Lexem;

Lexem get_next_lexem(char** string_ptr);

Lexem* parse_lexems(char** string_ptr);

#endif