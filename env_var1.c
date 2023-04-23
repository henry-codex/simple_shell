#include "shell.h"

/**
 * cmp_env_name - compares the name of an environment variable
 * with the given name.
 * @nenv: name of the environment variable
 * @name: name to compare against
 *
 * Return: The number of characters in the name of the environment variable
 * that match the given name, plus one. Returns 0 if the names do not match.
 */
int cmp_env_name(const char *nenv, const char *name)
{
	int i;

	/* Compare each character in the environment variable name with the
	 * corresponding character in the given name */
	for (i = 0; nenv[i] != '='; i++)
	{
		if (nenv[i] != name[i])
		{
			return (0);
		}
	}

	/* Return the number of matching characters plus one */
	return (i + 1);
}

/**
 * _getenv - retrieves the value of an environment variable.
 * @name: name of the environment variable to retrieve
 * @_environ: pointer to the array of environment variables
 *
 * Return: If the environment variable is found, returns a pointer to the
 * value of the variable. Otherwise, returns NULL.
 */
char *_getenv(const char *name, char **_environ)
{
	char *ptr_env;
	int i, mov;

	/* Initialize ptr_env to NULL */
	ptr_env = NULL;

	/* Search through the array of environment variables for the given name */
	for (i = 0; _environ[i]; i++)
	{
		/* Compare the name of the environment variable with the given name */
		mov = cmp_env_name(_environ[i], name);

		/* If the names match, set ptr_env to point to the value of the
		 * environment variable and break out of the loop */
		if (mov)
		{
			ptr_env = _environ[i];
			break;
		}
	}

	/* If the environment variable was found, return a pointer to its value */
	if (ptr_env != NULL)
	{
		return (ptr_env + mov);
	}
	/* Otherwise, return NULL */
	else
	{
		return (NULL);
	}
}

/**
 * _env - prints the values of all environment variables.
 * @datash: pointer to a data_shell struct
 *
 * Return: Always returns 1.
 */
int _env(data_shell *datash)
{
	int i, j;

	/* Loop through the array of environment variables */
	for (i = 0; datash->_environ[i]; i++)
	{
		/* Loop through the characters in the environment variable */
		for (j = 0; datash->_environ[i][j]; j++)
			;

		/* Write the environment variable to standard output */
		write(STDOUT_FILENO, datash->_environ[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}

	/* Set the status of the data_shell struct to 0 and return 1 */
	datash->status = 0;
	return (1);
}

