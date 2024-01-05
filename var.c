#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	/* checks for the '||' operator */
	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	/* checks for the '&&' operator */
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0; /* replace the first '&' with null to terminate the previous command */
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	/* Check for the ';' operator */
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	/* check if command buffer is CMD_AND */
	if (info->cmd_buf_type == CMD_AND)
	{
		/* terminate current command by replacing 'i' with null character if command exit status is true */
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	/* check if the command buffer is CMD_OR */
	if (info->cmd_buf_type == CMD_OR)
	{
		/* terminate current command by replacing 'i' with null if exit status is zero */
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j; /* update position 'p' to position 'j' */
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		/* check for an alias in the alias list that matches curent command */
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0); /* If no matching alias is found, return 0 */

		/*  Free the original command name stored in argv[0] */
		free(info->argv[0]);

		/* Find the position of '=' in the alias definition */
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		/* Check if the argument starts with '$' and has more than one character */
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue; /* Skip to the next iteration if the condition is not met */

		/* Check if the argument is "$?" */
		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			/* Replace the argument with the converted process ID */
			replace_string(&(info->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		/* Check if the argument corresponds to an environment variable */
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		/* If no match is found, replace the argument with an empty string */
		replace_string(&info->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
