#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
	/* Check if 'environ' is not initialized */
	if (!info->environ || info->env_changed)
	{
		/* Convert the linked list to strings */
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv(info_t *info, char *var)
{
	/* Init variables */
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	/* linked list or variable is not provided */
	if (!node || !var)
		return (0);

	while (node)
	{
		/* Check if the current variable starts with the specified 'var' */
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0; /* Reset the index and node for next iteration */
			node = info->env;
			continue;
		}
		/* Move to the next node and update the index */
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value) /* variable or value is not provided */
		return (0);

	/* allocate memory for concatenated string */
	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		/* Check if the current variable starts with the specified 'var' */
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			/* free the existing string */
			free(node->str);
			node->str = buf; /* update node string */
			info->env_changed = 1;
			return (0);
		}
		node = node->next; /* move to the next mode */
	}
	add_node_end(&(info->env), buf, 0);
	free(buf); /* free buffer */
	info->env_changed = 1;
	return (0);
}
