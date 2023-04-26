#include "main.h"
#include <sys/types.h>
#include <sys/stat.h>

char *get_location(char *command)
{
	char *path, *path_copy = NULL;
	char *file_path, *path_token = NULL;
	struct stat buffer;

	path = getenv("PATH");

	if (path)
	{
		path_copy = strdup(path);
		path_token = strtok(path_copy, ":");

		/* Go through dirrectories of PATH, if path_token/command exists*/
		while (path_token != NULL)
		{
			file_path = malloc(strlen(path_token) + strlen(command) + 2);
			strcpy(file_path, path_token);
			strcat(file_path, "/");
			strcat(file_path, command);
			strcat(file_path, "\0");

			/*printf("%s file path\n", file_path);*/
			/* stat is used to test if the filepath exists */
			if (stat(file_path, &buffer) == 0)
			{
				free(path_copy);
				return (file_path);
			}
			else
			{
				/* file_path does not exist, go to next token */
				free(file_path);
				path_token = strtok(NULL, ":");
			}

		}
		/* If the command itslef is a valid path */
		if (stat(command, &buffer) == 0)
		{
			free(path_copy);
			return (command);
		}
		free(path_copy);
		return (NULL);
	}
	return (NULL);
}
