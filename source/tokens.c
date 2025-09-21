#include "tokens.h"

#define readWhileToBuffer(_b, _l, _c) { u8 i = 0;                   \
                                        while((_c))                 \
                                        {                           \
                                            (_b)[i++] = *((_l)++);  \
                                        }                           \
                                        (_b)[i] = '\0'; }

static inline void advance(struct tokens *t, struct token **c)
{
    (*c)++;
    t->current_length++;
    if(t->current_length >= t->max_length)
    {
        t->max_length = t->max_length << 2;
        t->tokens = (struct token*)realloc(t->tokens, t->max_length * sizeof(struct token));
        assert(NULL != t->tokens, "failed to allocate more memory for tokens.", NULL);
    }
}

struct tokens *tokenise(char *content)
{
    struct tokens *t = (struct tokens *)malloc(1 * sizeof(struct tokens));
    assert(NULL != t, "failed to allocate memory for tokens", NULL);
    t->max_length = DEFAULT_TOKEN_AMMOUNT;
    t->current_length = 0;
    t->tokens = (struct token *)malloc(t->max_length * sizeof(struct token));
    assert(NULL != t->tokens, "failed to allocate memory for tokens", NULL);

    struct token *current = t->tokens;
    char *letter = content;
    while('\0' != *letter)
    {
        if(isspace(*letter))
        {
            letter++;
            continue;
        }

        // int | float | double
        if(isnumber(*letter))
        {
            bool isDecimal = false;
            char buffer[64];
            u8 i = 0;
            while(isnumber(*letter))
            {
                buffer[i++] = *(letter++);
            }
            if('.' == *letter)
            {
                isDecimal = true;
                buffer[i++] = '.';
                letter++;
                while(isnumber(*letter))
                {
                    buffer[i++] = *(letter++);
                }   
            }
            buffer[i] = '\0';

            if(isDecimal)
            {
                if('f' == peek(letter))
                {
                    letter++;
                    current->type = TOKEN_VALUE_FLOAT;
                    current->value.number_float = (float)atof(buffer);
                } else 
                {
                    current->type = TOKEN_VALUE_DOUBLE;
                    current->value.number_double = atof(buffer);
                }
            } else 
            {
                current->type = TOKEN_VALUE_INTEGER;
                current->value.number_integer = atoi(buffer);
            }
            advance(t, &current);
            continue;
        }

        // symbol
        if(isalpha(*letter) || '_' == *letter)
        {
            char buffer[64];
            readWhileToBuffer(buffer,
                              letter,
                              isalnum(*letter) || '_' == *letter);
             
            current->type = TOKEN_SYMBOL;
            current->value.string = strdup(buffer);
            printf("%s\n", current->value.string);
            advance(t, &current);
            continue;
        }

        switch(*letter)
        {
            case '@':
                letter++;
                char buffer[64];
                readWhileToBuffer(buffer,
                                  letter,
                                  isalnum(*letter) || '_' == *letter);
             
                current->type = TOKEN_DECORATOR;
                current->value.string = strdup(buffer);
                printf("@%s\n", current->value.string);
                advance(t, &current);
                break;
            default:
                break;
        }

        letter++;
    }

    current->type = TOKEN_END;

    return t;
} 