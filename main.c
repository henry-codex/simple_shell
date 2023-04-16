#include "main.h"
#include <string.h>
/**
 * - main - Entry point
 * @argc: arguments count
 * @argv: arguments
 *
 * Return: always 0
 */

int main(void)
{
	char *prompt = "MyShell $ ";
	char *lineptr = NULL;
	char *lineptr_copy = NULL;
	size_t n = 0;
	ssize_t bytes_read;
	int argc, num_tokens, i = 0;
	char *token = NULL;
	char **argv;

	const char *delim = " \n";

	(void)argc;
	while (1)
	{
		printf("%s", prompt);

		bytes_read = getline(&lineptr, &n, stdin);
		if (bytes_read == -1)
		{
			printf("%s\n", "Exiting shell....");
			return (-1);
		}
		lineptr_copy = malloc(sizeof(char) * bytes_read);
		if (lineptr_copy == NULL)
		{
			perror("tsh: memory allocation error");
			return(-1);
		}
		strcpy(lineptr_copy, lineptr);

		/* Get number of tokens it will be divided into */
		token = strtok(lineptr, delim);
		while (token != NULL)
		{
			num_tokens++;
			token = strtok(NULL, delim); 
		}
		num_tokens++;
		/* argv will be an array of strings */
		/* first allocate memory for the char pointers*/
		argv = malloc(sizeof(char *) * num_tokens);
		/* Using lineptr_copy fill argv with tokens */
		token = strtok(lineptr_copy, delim);
		for (i = 0; token != NULL; i++)
		{
			argv[i] = malloc(sizeof(char) * strlen(token));
			strcpy(argv[i], token);

			token = strtok(NULL, delim);
		}
		argv[i] = NULL;
		execmd(argv);

		free(lineptr);
		free(lineptr_copy);
		free(argv);
	}
	return (0);
}
