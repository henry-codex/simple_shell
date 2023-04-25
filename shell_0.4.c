#include "shell.h"

/**
 * exit_shell - exits the shell
 * @datash: data relevant (status and args)
 *
 * Return: 0 on success, -1 on failure
 */
int exit_shell(data_shell *datash)
{
    if (datash->args[1] != NULL)
    {
        printf("exit: too many arguments\n");
        return (-1);
    }

    free_datash(datash); /* Free memory allocated for data_shell */
    exit(EXIT_SUCCESS);

    /* The code will never reach here */
    return (0);
}

/* Define the structure for the builtin commands*/
typedef struct {
    char *name;
    int (*func)(data_shell *);
} builtin_t;

/* Define the builtin commands*/
builtin_t builtins[] = {
    {"exit", exit_shell},
};

