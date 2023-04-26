#include "main.h"

/**
 * __exit - a builtin exit
 *
 * @argv: array of arguments
 *
 * Return: always 0
 */
int __exit(char **argv)
{
	if (argv[1] != NULL)
		fprintf(stderr, "Exit arguments not handled yet");
	return (0);
}
