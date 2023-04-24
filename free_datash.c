#include "shell2.h"

void free_datash(data_shell *datash)
{
    int i;

    if (datash == NULL)
        return;

    if (datash->line != NULL)
        free(datash->line);

    for (i = 0; i < MAX_ARGS; i++) {
        if (datash->args[i] != NULL)
            free(datash->args[i]);
    }

    for (i = 0; i < MAX_COMMANDS; i++) {
        if (datash->commands[i] != NULL)
            free(datash->commands[i]);
    }

    free(datash);
}

