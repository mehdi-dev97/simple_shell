#include "main.h"

/**
 * *fill_memory - fills memory with byte constant
 * @s: memory pointer area
 * @b: the byte
 * @n: number of bytes filled
 *Return: (s) pointer memory area
 */
char *fill_memory(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * free_memory - free a string of strings
 * @pp: string of strings
 */
void free_memory(char **ptp)
{
	char **a = ptp;

	if (!ptp)
		return;
	while (*ptp)
		free(*ptp++);
	free(a);
}

/**
 * realloc_memory - reallocate memory
 * @ptr: previous pointer  malloc block
 * @old_size: byte size previous block
 * @new_size: byte size new block
 *
 * Return: pointer to da old block.
 */
void *realloc_memory(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}

/**
 * byte_free - free a pointer and NULL of the address
 * @ptr: address pointer to free
 *
 * Return: 1 free, or 0.
 */
int byte_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

