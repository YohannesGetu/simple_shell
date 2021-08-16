#include "shell.h"

/**
 * _realloc - reallocates a pointer to double the space
 * @ptr: pointer to the old array
 * @size: pointer to number of elements in the old array
 * @bytes: number of bytes in each element
 *
 * Return: pointer to the new array
 */
void *_realloc(char *ptr, size_t *size, size_t bytes)
{
	char *new;
	size_t i;

	new = malloc(bytes * ((*size) + 10));
	if (new == NULL)
	{
		free(ptr);
		return (NULL);
	}
	for (i = 0; i < (*size * bytes); i++)
	{
		new[i] = ptr[i];
	}
	*size += 10;
	free(ptr);
	return (new);
}
