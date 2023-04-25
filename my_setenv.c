#include "shell2.h"

/**
 * my_setenv - Set the value of an environment variable
 * @datash: Pointer to a data_shell struct containing the environment variables
 *
 * Return: 0 on success, or -1 on error
 */
int my_setenv(data_shell *datash)
{
    char *name, *value;
    int overwrite;

    /* Check for correct number of arguments */
    if (datash->args[1] == NULL || datash->args[2] == NULL || datash->args[3] != NULL)
    {
        fprintf(stderr, "Usage: setenv NAME VALUE [OVERWRITE]\n");
        return (-1);
    }

    name = datash->args[1];
    value = datash->args[2];

    /* Check if OVERWRITE is provided */
    if (datash->args[3] != NULL && strcmp(datash->args[3], "1") == 0)
        overwrite = 1;
    else
        overwrite = 0;

    /* Call _setenv function to set the environment variable */
    if (_setenv(name, value, overwrite) == -1)
    {
        fprintf(stderr, "Error setting environment variable\n");
        return (-1);
    }

    return (0);
}

/**
 * _setenv - Set the value of an environment variable
 * @name: The name of the variable
 * @value: The value to set
 * @overwrite: Whether to overwrite an existing variable with the same name
 *
 * Return: 0 on success, or -1 on error
 */
int _setenv(const char *name, const char *value, int overwrite)
{
    char *envvar;
    size_t len;
    int i;

    if (name == NULL || value == NULL)
        return (-1);

    len = strlen(name) + strlen(value) + 2;
    envvar = malloc(len);
    if (envvar == NULL)
        return (-1);

    sprintf(envvar, "%s=%s", name, value);

    /* Check if variable already exists */
    for (i = 0; environ[i] != NULL; i++)
    {
        if (strncmp(name, environ[i], strlen(name)) == 0 && environ[i][strlen(name)] == '=')
        {
            if (overwrite)
                environ[i] = envvar;
            else
            {
                free(envvar);
                return (0);
            }
        }
    }

    if (environ[i] == NULL)
    {
        if (i == MAX_ARGS - 1)
        {
            free(envvar);
            return (-1);
        }
        environ[i + 1] = NULL;
    }

    environ[i] = envvar;

    return (0);
}

