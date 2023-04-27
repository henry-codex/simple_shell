#include "main.h"
/**
 * _realloc - Reallocates a memory block to a new size.
 *
 * @ptr: A pointer to the previously allocated memory block.
 * @old_size: The previous size of the memory block in bytes.
 * @new_size: The new size of the memory block in bytes.
 *
 * Return: If successful, a pointer to the newly allocated memory block is
 *         returned. If new_size is 0 and ptr is not NULL, the memory block is
 *         freed and NULL is returned. Otherwise, NULL is returned and the
 *         contents of ptr are unchanged.
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *result;

	if (new_size == old_size)
		return (ptr);
	if (new_size == 0 && ptr)
	{
		free(ptr);
		return (NULL);
	}
	result = malloc(new_size);
	if (result == NULL)
		return (NULL);
	if (ptr == NULL)
	{
		fill_an_array(result, '\0', new_size);
		free(ptr);
	}
	else
	{
		_memcpy(result, ptr, old_size);
		free(ptr);
	}
	return (result);
}
/**
 * _memset - fills a memory with a constant byte
 *
 * @s: pointer to the memory area
 * @n: number of bytes to be filled
 * @byt: constant byte to be filled
 *
 * Return: pointer to the memory area s
 */
char *_memset(char *s, char byt, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
	{
		s[i] = byt;
	}
	return (s);
}
/**
 * free_data - frees the data structure
 * @data: pointer to the data structure
 *
 * Return: 1 on success, -1 on failure
 */
int free_data(sh_t *data)
{
	free(data->line);
	data->line = NULL;
	free(data->args);
	data->args = NULL;
	free(data->cmd);
	data->cmd = NULL;
	free(data->error_msg);
	data->error_msg = NULL;
	return (0);
}
/**
 * _memcpy - copies memory area
 * @dest: Destination memory area
 * @src: Source memory area
 * @n: Amount of memory byte
 *
 * Return: A pointer to dest
 */
char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
	{
		dest[i] = src[i];
	}
	return (dest);
}
