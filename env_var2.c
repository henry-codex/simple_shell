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

/**
 *_setenv - Set an environment variable.
 * @datash: Shell data struct.
 *
 * Return: Always returns 1.
 */
int _setenv(data_shell *datash)
{
    char *name, *value, *tmp;
    int i, len;

    for (i = 1; datash->args[i] != NULL; i++)
    {
        tmp = datash->args[i];
        len = 0;
        while (*tmp && *tmp != '=')
        {
            tmp++;
            len++;
        }
        name = malloc(sizeof(char) * (len + 1));
        if (name == NULL)
            return (0);
        strncpy(name, datash->args[i], len);
        name[len] = '\0';
        value = datash->args[i] + len + 1;
        set_env(name, value, datash);
    }
    return (1);
}

/**
 * _unsetenv - Remove an environment variable.
 * @datash: Shell data struct.
 *
 * Return: Always returns 1.
 */
int _unsetenv(data_shell *datash)
{
    int i, j;

    if (datash->args[1] == NULL)
    {
        dprintf(STDERR_FILENO, "Usage: unsetenv VARIABLE\n");
        return (1);
    }
    for (i = 1; datash->args[i] != NULL; i++)
    {
        for (j = 0; datash->env[j] != NULL; j++)
        {
            if (cmp_env_name(datash->env[j], datash->args[i]) == 0)
            {
                free(datash->env[j]);
                for (; datash->env[j + 1] != NULL; j++)
                    datash->env[j] = datash->env[j + 1];
                datash->env[j] = NULL;
                break;
            }
        }
    }
    return (1);
}

