#include "shell2.h"

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

