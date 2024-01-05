#include "shell.h"

/**
 **_memset - fills memory with a constant byte
 *@s: the pointer to the memory area
 *@b: the byte to fill *s with
 *@n: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	/* Loop through each byte in the memory area pointed to by s */
	for (i = 0; i < n; i++)
		/* Set the current byte to the constant byte b */
		s[i] = b;
	/* Return the pointer to the modified memory area */
	return (s);
}

/**
 * ffree - frees a string of strings
 * @pp: string of strings
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	/* If the original pointer is NULL, allocate new memory with the specified size */
	if (!ptr)
		return (malloc(new_size));
	/* If the new size is zero, free the original memory and return NULL */
	if (!new_size)
		return (free(ptr), NULL);
	/* If the new size is the same as the old size, no reallocation is needed */
	if (new_size == old_size)
		return (ptr);

	/* Allocate new memory with the specified new size */
	p = malloc(new_size);
	if (!p)
		return (NULL);

	/* Copy the contents from the original memory block to the new memory block */
	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	/* Free the original memory block */
	free(ptr);
	/* Return the pointer to the reallocated block of memory */
	return (p);
}
