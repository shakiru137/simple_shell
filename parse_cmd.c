#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	/* Declare a struct to hold file status information */
	struct stat st;

	/* Ignore the 'info' parameter */
	(void)info;
	/* Check if 'path' is NULL */
	if (!path || stat(path, &st))
		return (0);

	/* Check if the file is a regular file */
	if (st.st_mode & S_IFREG)
	{
		return (1); /* return 1 if the file is a regular file */
	}
	return (0); /* return 0 if the file is not a regular file */
}

/**
 * dup_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0; /* Null-terminate the buffer to create a valid C string */
	return (buf);
}

/**
 * find_path - finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr) /* Check if 'pathstr' is NULL */
		return (NULL);
	/* Check if 'cmd' is a relative path starting with "./" */
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		/* Check for the end of the string or a colon delimiter in 'pathstr' */
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i);
			/* If the path is empty, add 'cmd' to it; else, add a '/' first */
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	/* Return NULL if no valid path is foun */
	return (NULL);
}
