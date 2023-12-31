#include "shell.h"
/**
 * interactive - checks if the shell is in interactive mode
 * @info: struct containing shell information
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}
/**
 * is_delim - checks if a character is a delimiter
 * @c: the character to check
 * @delim: the delimiter string against which to check
 *
 * Return: 1 if the character is a delimiter, 0 otherwise.
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - checks if a character is alphabetic
 * @c: the character to be checked
 *
 * Return: 1 if the character is alphabetic, 0 otherwise
 */
int _isalpha(int c)
{
	/* Check if the character is lowercase or uppercase alphabets */
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1); /* return 1 if character is an alphabet */
	else
		return (0); /* return 0, otherwise */
}

/**
 *_atoi - converts a string to an integer
 *@s: the string to be converted
 *
 *Return: 0 if no numbers in string
 */
int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		/*  Check if the character is a digit */
		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	/* Adjust the output based on the sign */
	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output); /* return the converted integer */
}
