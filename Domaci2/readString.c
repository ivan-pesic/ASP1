#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readString() {
    char* str = NULL, c;
    int i = 0;
    c = getchar();
    c = getchar();
    while (c != '\n') {
        str = realloc(str, (i + 1) * sizeof(char));
        if (str == NULL)
            exit(EXIT_FAILURE);
        *(str + (i++)) = c;
        c = getchar();
    }
    str = realloc(str, (i + 1) * sizeof(char));
    if (str == NULL)
        exit(EXIT_FAILURE);
    str[i] = '\0';
    return str;
}