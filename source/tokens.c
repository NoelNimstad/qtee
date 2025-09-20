#include "tokens.h"

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

        if(isnumber(*letter))
        {
            bool isDecimal = false;
            char buffer[64];
            u8 i;
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

            current->type = isDecimal ? TOKEN_VALUE_FLOAT : TOKEN_VALUE_INTEGER;
            if(isDecimal)
            {
                current->value.number_float = atof(buffer);
            } else 
            {
                current->value.number_integer = atoi(buffer);
            }
            advance(t, &current);
            continue;
        }

        if(isalpha(*letter) || '_' == *letter)
        {
            char buffer[64];
            u8 i;
            while(isalnum(*letter) || '_' == *letter)
            {
                buffer[i++] = *(letter++);
            }
            buffer[i] = '\0';

            current->type = TOKEN_SYMBOL;
            current->value.string = strdup(buffer);
            advance(t, &current);
            continue;
        }

        letter++;
    }

    return t;
}