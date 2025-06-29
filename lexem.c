#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "tiny-regex-c/re.h"

typedef enum {
    LEXEM_FLOAT,
    LEXEM_INTEGER,
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

char* patterns[] = {
    "^[+-]?[0-9]+\\.[0-9]*",
    "^[+-]?[0-9]+",
    "^\\+",
    "^\\-",
    "^\\*",
    "^\\/",
    "^\\^",
    "^sqrt",
    "^\\(",
    "^\\)",
};

typedef struct {
    LexemType type;
    char* value;
} Lexem;

Lexem get_next_lexem(char** string_ptr) {
    Lexem lexem = {LEXEM_UNKNOWN, NULL};
    char* string = *string_ptr;

    // Skip spaces
    while (isspace(*string)) {
        string++;
        (*string_ptr)++;
    }

    // Check if string is EOF
    if (*string == '\0') {
        lexem.type = LEXEM_EOF;
        lexem.value = malloc(1);
        *lexem.value = '\0';
        return lexem;
    }

    size_t patterns_number = sizeof(patterns) / sizeof(patterns[0]);

    for (int i = 0; i < patterns_number; i++) {
        int match_length;
        re_t pattern = re_compile(patterns[i]);

        // if no match then skip
        if (re_matchp(pattern, string, &match_length) == -1) {
            continue;
        }

        lexem.type = i;
        lexem.value = malloc(match_length + 1);
        strncpy(lexem.value, string, match_length);
        lexem.value[match_length] = '\0';
        string += match_length;
        (*string_ptr) += match_length;
        return lexem;
    }

    fprintf(stderr, "\nUnknown lexem\n");
    exit(1);
}

Lexem* parse_lexems(char** string_ptr) {
    Lexem* lexems = NULL;
    size_t size = 0;

    for (Lexem lexem = get_next_lexem(string_ptr); lexem.type != LEXEM_EOF; lexem = get_next_lexem(string_ptr)) {
        lexems = (Lexem*)realloc(lexems, (size + 1) * sizeof(Lexem));
        lexems[size] = lexem;
        size++;
    }

    return lexems;
}