#include "shell.h"

/**
 * exit_shell - exits the shell
 *
 * @datash: data relevant (status and args)
 * Return: 0 on success.
 */
int exit_shell(data_shell *datash)
{
	if (datash->args[1] != NULL) {
		printf("exit: too many arguments\n");
		return 1;
	}

	return 0;
}

