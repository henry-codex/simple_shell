#include "main.h"
#include "builtins.h"

/**
 *_launch - launches the command
 *
 * @argv: arguments array
 *
 * Return: int
 */
int _launch(char **argv)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == 0)
	{
		if (execvp(argv[0], argv) == -1)
		{
			perror("hsh");
		}
		printf("\n");
		exit(EXIT_FAILURE);
	}
	else if (child_pid < 0)
	{
		perror("hsh");
	}
	else
	{
		do
		{
			waitpid(child_pid, &status, WUNTRACED);
		}
		while (!WIFEXITED(status) && !WIFSIGNALED(status));

	}
	return (1);

}
/**
 * execmd - execute procedur
 *
 * @argv: array of arguments
 *
 * Return: int
 */
int execmd(char **argv)
{
	char *command = NULL;
	int i;

	if (argv)
	{
		command = argv[0];

		/*printf("%s command", command);*/
		for (i = 0; i < len_builtin_func(); i++)
		{
			if (strcmp(argv[0], builtins[i].name) == 0)
			{
				/*printf("%s comand ", argv[0]);*/
				return (builtins[i].func(argv));
			}
		}
		command = get_location(command);
		if (command != NULL)
		{
			return (_launch(argv));
		}
		else
		{
			fprintf(stderr, "hsh: command not found: %s\n", argv[0]);
			return (127);
		}

	}
	else
	{
		return (1);
	}
}
