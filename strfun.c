#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @s: the string whose length to check
 *
 * Return: integer length of string
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s) /* heck if the input string is empty */
		return (0); /* return 0 If the string is NULL */

	while (*s++)
		i++;
	return (i); /* Return the calculated length of the string */
}

/**
 * _strcmp - performs lexicogarphic comparison of two strangs.
 * @s1: the first strang
 * @s2: the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2) /* strings are equal */
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1); /* Return -1 if s1 */
	/* is less than s2, 1 if s1 is greater than s2 */
}

/**
 * starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		/* Compare characters in haystack and needle strings */
		if (*needle++ != *haystack++)
			return (NULL); /* Return NULL if characters don't match */
	return ((char *)haystack);
}

/**
 * _strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	/* Move to the end of the destination string */
	while (*dest)
		dest++;
	/* copy characters from source string to destination string */
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
