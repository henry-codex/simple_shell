#include "shell.h"

/**
 * _env - prints the current environment
 *
 * @datash: data relevant (status and args)
 * Return: Always 0.
 */
int _env(data_shell *datash)
{
	char **env;

	for (env = datash->env; *env; env++)
		printf("%s\n", *env);

	datash->status = 0;
	return (0);
}

