#ifndef TOKENS_H
#define TOKENS_H

#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "types.h"
#include "console.h"

#define DEFAULT_TOKEN_AMMOUNT   (2 << 8)

enum ttype
{
    TOKEN_HASH_COMMAND,
    TOKEN_DECORATOR,
    TOKEN_SYMBOL,
    TOKEN_TEXT,
    TOKEN_VALUE_INTEGER,
    TOKEN_VALUE_FLOAT,
    TOKEN_END
};

struct token
{
    enum ttype type;
    union
    {
        // string
        char *string;
        // numbers
        float number_float;
        double number_double;
        int number_integer;
    } value;
};

struct tokens
{
    u32 max_length;
    u32 current_length;
    struct token *tokens;
};

struct tokens *tokenise(char *content);

#endif