#include "shell2.h"

/**
 * _getenv - retrieves an environment variable
 * @name: name of the variable
 *
 * Return: pointer to the value of the environment variable, or NULL if not found
 */
char *_getenv(const char *name)
{
    int i, j;
    char *envname, *value;
    
    for (i = 0; environ[i]; i++)
    {
        envname = environ[i];
        for (j = 0; name[j] && envname[j] == name[j]; j++)
        {
            if (envname[j + 1] == '=')
            {
                value = envname + j + 2;
                return (value);
            }
        }
    }
    return (NULL);
}

/**
 * get_path - searches for a program in the PATH environment variable
 * @command: name of the command to search for
 *
 * Return: pointer to the full path of the command, or NULL if not found
 */
char *get_path(char *command)
{
    char *path, *dir, *fullpath;
    struct stat st;

    /* Check if the command is a path */
    if (command[0] == '/')
    {
        if (stat(command, &st) == 0)
            return (command);
        return (NULL);
    }
    
    /* Check if the command is in the current directory */
    if (stat(command, &st) == 0)
    {
        fullpath = strdup(command);
        return (fullpath);
    }
    
    /* Search for the command in the PATH */
    path = _getenv("PATH");
    if (path == NULL)
        return (NULL);
    while (*path != '\0')
    {
        dir = path;
        while (*dir != ':' && *dir != '\0')
            dir++;
        if (*dir == ':')
            *dir = '\0';
        fullpath = build_path(dir, command);
        if (stat(fullpath, &st) == 0)
            return (fullpath);
        free(fullpath);
        path = (*dir == '\0') ?
            NULL : dir + 1;
    }
    return (NULL);
}

/**
 * build_path - concatenates a directory and a file name
 * @dir: directory name
 * @command: file name
 *
 * Return: pointer to a string containing the concatenated directory and file name
 */
char *build_path(char *dir, char *command)
{
    char *path;
    int dirlen, cmdlen, pathlen, i, j;

    dirlen = strlen(dir);
    cmdlen = strlen(command);
    pathlen = dirlen + cmdlen + 2;

    path = malloc(sizeof(char) * pathlen);
    if (path == NULL)
        return (NULL);

    for (i = 0; i < dirlen; i++)
        path[i] = dir[i];
    path[i] = '/';
    i++;
    for (j = 0; j < cmdlen; j++)
        path[i + j] = command[j];
    path[i + j] = '\0';

    return (path);
}

