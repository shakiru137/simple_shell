#include "shell.h"

/**
 * clear_info - initializes info_t struct
 * @info: struct address
 */
void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void set_info(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		/* check if 'strtow' failed to split 'arg' */
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			/* check if memory allocation was successful */
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				/* Set the 2nd element of 'argv' to NULL */
				info->argv[1] = NULL;
			}
		}
		/* Count the number of elements in 'argv' and set 'argc' accordingly */
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replace_alias(info); /* replace aliases in 'info' */
		replace_vars(info); /* replace variables in 'info' */
	}
}

/**
 * free_info - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void free_info(info_t *info, int all)
{
	/* Free the memory allocated for the 'argv' array */
	ffree(info->argv);
	info->argv = NULL;
	/* set the 'path' member of the 'info'structure to NULL */
	info->path = NULL;
	if (all) /* check if 'all' flag is true */
	{
		/* check if 'cmd_buf' is not allocated */
		if (!info->cmd_buf)
			free(info->arg);
		/* check if 'env' list is allocated */
		if (info->env)
			free_list(&(info->env)); /* free 'env' list */
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		/* heck if 'readfd' is greater than 2 */
		if (info->readfd > 2)
			close(info->readfd); /* close file descriptor */
		_putchar(BUF_FLUSH); /* flush the output buffer */
	}
}
