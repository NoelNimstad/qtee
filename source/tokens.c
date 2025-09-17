#include "tokens.h"

struct tokens *tokenise(char *content)
{
    struct tokens *t = (struct tokens *)malloc(1 * sizeof(struct tokens));
    assert(NULL != t, "failed to allocate memory for tokens", NULL);
    t->length = DEFAULT_TOKEN_AMMOUNT;
    t->tokens = (struct token *)malloc(t->length * sizeof(struct token));
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
            bool isDecimal;
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
            continue;
        }

        letter++;
    }

    return t;
}