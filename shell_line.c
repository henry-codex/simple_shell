#include "shell.h"

#define BUFSIZE 1024

/**
 * get_line - reads input from stream and stores it in a buffer
 * @lineptr: pointer to buffer that will store the input
 * @n: pointer to size of buffer
 * @stream: stream to read input from
 *
 * Return: number of characters read on success, -1 on failure
 */
ssize_t get_line(char **lineptr, size_t *n, FILE *stream)
{
	static char buffer[BUFSIZE];
	static size_t buf_pos, buf_size;
	size_t i;
	ssize_t bytes_read;

	if (!lineptr || !n || !stream)
		return (-1);

	if (*n == 0 || !*lineptr)
	{
		*n = BUFSIZE;
		*lineptr = malloc(*n);
		if (!*lineptr)
			return (-1);
	}

	for (i = 0; i < *n; i++)
	{
		if (buf_pos >= buf_size)
		{
			bytes_read = read(fileno(stream), buffer, BUFSIZE);
			if (bytes_read == -1)
				return (-1);
			if (bytes_read == 0 && i == 0)
				return (-1);
			buf_pos = 0;
			buf_size = (size_t)bytes_read;
		}

		(*lineptr)[i] = buffer[buf_pos++];
		if ((*lineptr)[i] == '\n')
		{
			i++;
			break;
		}
	}

	(*lineptr)[i] = '\0';
	return ((ssize_t)i);
}

