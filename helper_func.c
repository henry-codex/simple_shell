#include "main.h"
#include "builtins.h"
/**
 * len_builtin_func - get the lenth of builtin funcs
 *
 * Return: size
 */
int len_builtin_func(void)
{
	size_t size;

	size = sizeof(builtins) / sizeof(builtin_t);
	return (size);
}
