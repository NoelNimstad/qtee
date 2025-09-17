#include <stdio.h>
#include "console.h"
#include "file.h"

int main(int argc, char const *argv[])
{
    assert(argc >= 2, "not enough arguments", NULL);
    compileFile(argv[1]);

    return 0;
}