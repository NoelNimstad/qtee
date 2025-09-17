#ifndef FILE_H
#define FILE_H

#include <stdlib.h>
#include <stdio.h>
#include "console.h"
#include "types.h"
#include "tokens.h"

void compileFile(const char *path)
{
    FILE *file = fopen(path, "r");
    assert(NULL != file, "file %s does not exist", path);
    u64 fileLength;
    fseek(file, 0, SEEK_END);
    fileLength = ftell(file);
    fseek(file, 0, SEEK_SET);
    inform("file %s is %llub long.", path, fileLength);
    char *fileContents = (char *)malloc(fileLength * sizeof(char));
    fread(fileContents, sizeof(char), fileLength + 1, file);
    fileContents[fileLength] = '\0';
    fclose(file);

    struct tokens *t = tokenise(fileContents);
    free(fileContents);

    free(t);
    inform("compiled %s!", path);
}

#endif 