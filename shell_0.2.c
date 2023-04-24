#include "shell.h"

/**
 * execute_command_args - Executes the specified command with arguments.
 * @command: Command to execute.
 * @args: Array of arguments.
 */
void execute_command_args(char *command, char **args)
{
	pid_t pid;
	int status;

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		return;
	}
	else if (pid == 0)
	{
		if (execvp(command, args) == -1)
			perror("execve");

		exit(EXIT_FAILURE);
	}
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}

/**
 * parse_command - Parses a command line into arguments.
 * @line: Command line to parse.
 * @args: Array of arguments.
 *
 * Return: Number of arguments.
 */
int parse_command(char *line, char **args)
{
	int i = 0;
	char *token;

	token = strtok(line, " ");

	while (token != NULL && i < MAX_ARGS - 1)
	{
		args[i] = token;
		i++;
		token = strtok(NULL, " ");
	}

	args[i] = NULL;

	return (i);
}

/**
 * main - Simple UNIX command line interpreter.
 *
 * Return: Always 0.
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char **args = malloc(sizeof(char *) * MAX_ARGS);
	int argc;

	while (1)
	{
		int i; /* Declare i at the beginning of the while loop */

		printf("$ "); /* Display prompt */

		nread = getline(&line, &len, stdin); /* Read command line */

		if (nread == -1) /* Handle "end of file" condition */
		{
			putchar('\n');
			break;
		}

		line[nread - 1] = '\0'; /* Remove trailing newline */

		argc = parse_command(line, args);

		if (argc > 0)
		{
			if (access(args[0], F_OK) == 0) /* Check if file exists */
				execute_command_args(args[0], args);
			else /* Command not found */
				printf("Command not found: %s\n", args[0]);
		}

		for (i = 0; args[i] != NULL; i++) /* Reset arguments */
		{
			args[i] = NULL;
		}
	}
	free(line); /* Free memory allocated for line */
	free(args); /* Free memory allocated for arguments */
	return (EXIT_SUCCESS);
}
