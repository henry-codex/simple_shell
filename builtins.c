#include "shell.h"

/**
 * get_builtin - Get the corresponding builtin function for a command.
 * @cmd: The command.
 *
 * Return: If a builtin corresponding to @cmd exists, return a pointer to the
 * corresponding function. Otherwise, return NULL.
 */
int (*get_builtin(char *cmd))(data_shell *)
{
    static const struct {
        const char *name;
        int (*func)(data_shell *);
    } builtins[] = {
        {"exit", exit_shell},
        {"cd", change_dir},
        {"setenv", _setenv},
        {"unsetenv", _unsetenv},
        {"help", get_help},
        {"env", my_env},
        {NULL, NULL}
    };
    int i;

    for (i = 0; builtins[i].name; i++)
    {
        if (strcmp(builtins[i].name, cmd) == 0)
            return (builtins[i].func);
    }
    return (NULL);
}

