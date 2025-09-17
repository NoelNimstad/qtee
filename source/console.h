#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdlib.h>
#include <stdio.h>
#include "colors.h"

#define assert(_s, _t, ...) { if(!(_s)){ printf("\x1B[31mfatal error: \x1B[0m"); \
                                         printf((_t), __VA_ARGS__); \
                                         printf(".\n"); \
                                         exit(1); }; }
#define inform(_t, ...) { printf("\x1B[32minformation: \x1B[0m"); \
                          printf((_t), __VA_ARGS__); \
                          printf("\n"); }

#endif