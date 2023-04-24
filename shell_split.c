#include "shell.h"

/**
 * split_line - splits a string into an array of tokens
 * @line: the string to be split
 *
 * Return: an array of tokens or NULL on failure
 */
char **split_line(char *line)
{
	char **args = NULL;
	int i, j, k, len, num_args = 0;

	if (!line)
	{
		return (NULL);
	}
		len = strlen(line);

/* count number of arguments */
	for (i = 0; i < len; i++)
	{
		if (line[i] != ' ' && (i == 0 || line[i - 1] == ' '))
			num_args++;
	}

/* allocate memory for arguments array */
	args = malloc(sizeof(char *) * (num_args + 1));
	if (!args)
		return (NULL);

/* populate arguments array */
	for (i = 0, j = 0; i < num_args; i++)
	{
		while (line[j] == ' ')
			j++;

		k = j;
		while (line[j] != ' ' && line[j] != '\0')
			j++;

		args[i] = malloc(sizeof(char) * (j - k + 1));
		if (!args[i])
		{
			for (i--; i >= 0; i--)
			free(args[i]);
			free(args);
			 return (NULL);
		}

		memcpy(args[i], line + k, j - k);
		args[i][j - k] = '\0';
	}

	args[num_args] = NULL;
	return (args);
}
