#include "shell.h"

/**
 * bfree - frees a pointer and NULLs the address
 * @ptr: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr); /* free memory by input pointer */
		*ptr = NULL;
		return (1); /* Return 1 to indicate success */
	}
	return (0); /* return 0 if input pointer is NULL */
}
