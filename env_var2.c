#include "shell2.h"

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
        {"exit", my_exit_shell},
        {"cd", change_dir},
        {"setenv", my_setenv},
        {"unsetenv", _unsetenv},
        {"help", get_help},
        {"env", me_env},
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
 * exit_shell - Exit the shell.
 * @datash: Shell data struct.
 *
 * Return: Always returns 0.
 */
int my_exit_shell(data_shell *datash)
{
    free_datash(datash);
    exit(EXIT_SUCCESS);
}

/**
 * change_dir - Change the current working directory.
 * @datash: Shell data struct.
 *
 * Return: Always returns 1.
 */
int change_dir(data_shell *datash)
{
    if (datash->args[1] == NULL)
    {
        dprintf(STDERR_FILENO, "cd: expected argument to \"cd\"\n");
    }
    else
    {
        if (chdir(datash->args[1]) != 0)
        {
            perror("cd");
        }
    }
    return (1);
}

/**
 * _setenv - Set an environment variable.
 * @datash: Shell data struct.
 *
 * Return: Always returns 1.
 */
int set_env_2(char *name, char *value)
{
    char *new_var;
    size_t len_name, len_value, len_var;
    int i;

    len_name = strlen(name);
    len_value = strlen(value);
    len_var = len_name + len_value + 2;

    new_var = malloc(len_var * sizeof(char));
    if (!new_var)
    {
        perror("setenv");
        return (-1);
    }

    for (i = 0; name[i]; i++)
        new_var[i] = name[i];

    new_var[i] = '=';

    for (i = 0; value[i]; i++)
        new_var[len_name + 1 + i] = value[i];

    new_var[len_var - 1] = '\0';

    if (putenv(new_var) != 0)
    {
        perror("setenv");
        return (-1);
    }

    return (0);
}



/**
 * _unsetenv - Unset an environment variable.
 * @datash: Shell data struct
 *
 * Return: Always returns 1.
 */
int _unsetenv(data_shell *datash)
{
    if (datash->args[1] == NULL)
    {
        dprintf(STDERR_FILENO, "unsetenv: expected argument to \"unsetenv\"\n");
    }
    else
    {
        if (unsetenv(datash->args[1]) != 0)
        {
            perror("unsetenv");
        }
    }
    return (1);
}

/**
 * get_help - Print the help message.
 * @datash: Shell data struct.
 *
 * Return: Always returns 1.
 */
int get_help(data_shell *datash)
{
    (void)datash;

    printf("Simple Shell: a basic shell program\n"
           "Commands:\n"
           "  exit - Exit the shell.\n"
           "  cd - Change the current working directory.\n"
           "  setenv - Set an environment variable.\n"
           "  unsetenv - Unset an environment variable.\n"
           "  help - Display this help message.\n"
           "  env - Print the current environment.\n");

    return (1);
}

/**
 * my_env - Print the current environment.
 * @datash: Shell data struct.
 *
 * Return: Always returns 1.
 */
int me_env(data_shell *datash)
{
    int i;

    (void)datash;
    for (i = 0; environ[i] != NULL; i++) {
        printf("%s\n", environ[i]);
    }
    return 1;
}
