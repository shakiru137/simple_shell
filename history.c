#include "shell.h"

/**
 * get_history_file -  to get the history file
 * @info: parameter struct
 *
 * Return: The allocated string containg history file
 */

char *get_history_file(info_t *info)
{
	char *buf, *dir;

	/* value of the "HOME" environment variable */
	dir = _getenv(info, "HOME=");
	/* return NULL if "HOME"variable is not set */
	if (!dir)
		return (NULL);
	/* allocate memory for buffer */
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf) /* return NULL if memory allocation fails */
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir); /* copy directory string to buffer */
	_strcat(buf, "/"); /* Concatenate a "/" to the buffer */
	_strcat(buf, HIST_FILE);
	return (buf); /* return constructed buffer */
}

/**
 * write_history - to creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, -1 otherwise
 */
int write_history(info_t *info)
{
	ssize_t fd; /* file descriptor for history file */
	char *filename = get_history_file(info);/* full path to the history file */
	list_t *node = NULL; /* node pointer */

	/* return 1 if getting the history file path fails */
	if (!filename)
		return (-1);

	/* open history file */
	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename); /* free memory allocated for history file path */
	if (fd == -1) /* return 1 if opening file fails */
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd); /* write each history entry to file */
		_putfd('\n', fd); /* write a new line */
	}
	_putfd(BUF_FLUSH, fd); /* flush the buffer to the file */
	close(fd); /* close the file descriptor */
	return (1);
}

/**
 * read_history - will reads history from file
 * @info: the parameter struct
 *
 * Return: the histcount on success, 0 otherwise
 */
int read_history(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	/* return if getting the history file path fails */
	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);/* open the history file for reading */
	free(filename); /* free the allocated memory for the history file path */
	if (fd == -1)
		return (0); /* return 0 if opening of file fails */
	if (!fstat(fd, &st)) /* get size of history file */
		fsize = st.st_size;
	if (fsize < 2) /* If the file size is less than 2, return 0 */
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	/* read the contents of the file into buffer */
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)/* if reading fails free the buffer and return 0 */
		return (free(buf), 0);
	close(fd); /* close the fie descriptor */
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0; /* replace newline with NULL terminator */
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(info, buf + last, linecount++);
	free(buf); /* free the buffer memory */
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);/* renumber the history entries */
	return (info->histcount);/* return 1 to indicate success */
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}

/**
 * build_history_list - to add entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0.
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	/* if history list is not empty, set the node pointer to the start */
	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	/* if history list was empty, update the structure's history pointer */
	if (!info->history)
		info->history = node;
	return (0); /* return 0 to indicate success */
}

