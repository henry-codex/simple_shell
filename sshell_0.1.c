#include "shell.h"

/**
 * _getline - Reads an entire line from stream.
 * @lineptr: Pointer to buffer.
 * @n: Size of buffer.
 * @stream: Pointer to file stream.
 *
 * Return: Number of characters read or -1 on failure.
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	ssize_t nread;

	nread = getline(lineptr, n, stream);

	if (nread == -1)
		perror("getline");

	return (nread);
}

/**
 * execute_command - Executes the specified command.
 * @command: Command to execute.
 */
void execute_command(char *command)
{
	pid_t pid;
	char **argv;
	int argc = 2;

	argv = malloc(argc * sizeof(char *));
	if (!argv)
	{
		perror("malloc");
		return;
	}

	argv[0] = command;
	argv[1] = NULL;

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		free(argv);
		return;
	}
	else if (pid == 0)
	{
		if (execve(command, argv, NULL) == -1)
			perror("execve");
		exit(EXIT_FAILURE);
	}
	else
		wait(NULL);

	free(argv);
}

/**
 * my_main - Simple UNIX command line interpreter.
 *
 * Return: Always 0.
 */
int my_main(void)
{
	char *command = NULL;
	size_t bufsize = 0;
	ssize_t nread;

	while (1)
	{
		printf("$\t"); /* Display prompt */

		nread = _getline(&command, &bufsize, stdin); /* Read command line */

		if (nread == -1) /* Handle "end of file" condition */
		{
			putchar('\n');
			break;
		}

		command[nread - 1] = '\0'; /* Remove trailing newline */

		if (access(command, F_OK) == 0) /* Check if file exists */
			execute_command(command);
		else /* Command not found */
			printf("Command not found:\t%s\n", command);
	}

	free(command); /* Free memory allocated for command */

	return (EXIT_SUCCESS);
}

