#include "main.h"
void execmd(char **argv)
{
	char *command = NULL;

	if (argv)
	{
		command = argv[0];
		command = get_location(command);
		printf("%s command\n", command);
		if (execve(command, argv, NULL) == -1)
		{
			perror("Error encountered: ");
		}
	}
}
