#include "shell.h"

/**
 *_eputs - is used to prints an input string
 * @str: string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	int j = 0;

	if (!str) /* input string is not provided */
		return;
	while (str[j] != '\0')
	{
		_eputchar(str[j]);
		j++;
	}
}

/**
 * _eputchar - is used to writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.On error, -1 is returned,
 * and errno is set appropriately.
 */
int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	/* Check if the character is a buffer flush signal or if the buffer is full */
	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i); /* Write the contents of the buffer to standard error */
		i = 0; /* reset index */
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1); /* return 1 for success */
}

/**
 * _putfd - is used writes the character c to given fd
 * @c: The character to printed
 * @fd: The filedescriptor to write into
 *
 * Return: On success 1. On error, -1 is returned,
 * and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE]; /* init static variable for buffer */

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1); /* return 1 for success */
}

/**
 *_putsfd - is used to prints an input string
 * @str: string to be printed
 * @fd: filedescriptor to write into
 *
 * Return: the number of chars put
 */
int _putsfd(char *str, int fd)
{
	int j = 0;

	/* check if input string is not provided */
	if (!str)
		return (0);
	while (*str)
	{
		j += _putfd(*str++, fd);
	}
	return (j); /* return total number of characters written */
}
