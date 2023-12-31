#include "shell.h"

/**
 * list_len - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t list_len(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next; /* move to next node in the linked list */
		i++;
	}
	return (i); /* return final count */
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !i) /* Check if the linked list is NULL */
		return (NULL);
	/* allocate memory for array of strings */
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		/* allocate memory for individual string */
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			/*  If memory allocation fails, free the previously allocated memory */
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str; /* assign the pointer to the copied string */
	}
	strs[i] = NULL; /* add NULL terminator */
	return (strs); /* return pointers tto the array of strings */
}


/**
 * print_list - prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *h)
{
	size_t i = 0;

	while (h) /* loop through linked list */
	{
		_puts(convert_number(h->num, 10, 0)); /* print the current node's number */
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n"); /* print a new line */
		h = h->next;
		i++;
	}
	return (i); /* return total number of nodes in linked list */
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t i = 0; /* init counter variable */

	while (head)
	{
		/* check if current node is the same as the target node */
		if (head == node)
			return (i);
		/* move to the next node in the linked list */
		head = head->next;
		i++;
	}
	return (-1);
}
