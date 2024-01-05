#include "shell.h"

/**
 * _strcpy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */

/* function to copy the contents of one string to another */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	/* Check if the source and destination strings are the same or if the source is NUL */
	if (dest == src || src == 0)
		return (dest); /* If NULL, return the destination string without copying anything */
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	/* Add a null terminator to the destination string to ensure it is properly terminated */
	dest[i] = 0;
	return (dest);
}

/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */

/* function to duplicate a string and return a pointer to the duplicated string */
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	/* Allocate memory for the duplicated string */
	ret = malloc(sizeof(char) * (length + 1));
	/*  if memory allocation was not successful, return NULL */
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	/* return a pointer to the duplicated string */
	return (ret);
}

/**
 *_puts - prints an input string
 *@str: the string to be printed
 *
 * Return: Nothing
 */
/* function to print a string to the standard output */
void _puts(char *str)
{
	int i = 0;

	/* if the input string is NULL, return without doing anthing */
	if (!str)
		return;
	/* Iterate through the string until there is a null terminator */
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
/* function to write a character to the standard output, with buffering */
int _putchar(char c)
{
	/* static variable to keep track of the current position in the buffer */
	static int i;
	/* static buffer to temporarily store characters before writing to the standard output */
	static char buf[WRITE_BUF_SIZE];

	/* if the character is a buffer flush signal or if the buffer is full */
	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		/* write the contents of the buffer to the standard output */
		write(1, buf, i);
		i = 0; /* Reset the buffer position */
	}
	/* if the character is not a buffer flush signal */
	if (c != BUF_FLUSH)
		/* add the character to the buffer and increment the buffer position */
		buf[i++] = c;
	return (1); /* return 1 for success */
}
