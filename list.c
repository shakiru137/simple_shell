#include "shell.h"

/**
 * add_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	/* Check if the 'head' pointer is NULL */
	if (!head)
		return (NULL);
	/* Allocate memory for a new node */
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	/* Initialize the new node with zeros using _memset */
	_memset((void *)new_head, 0, sizeof(list_t));
	/* Set the 'num' field of the new node */
	new_head->num = num;
	if (str) /* if 'str'is not NULL, duplicate string */
	{
		new_head->str = _strdup(str);
		/* Check if string duplication was successful */
		if (!new_head->str)
		{
			free(new_head); /*  Free allocated memory */
			return (NULL); /* return NULL in case of failure */
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head); /* Return a pointer to the new node */
}

/**
 * add_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	/* If 'str' is not NULL, duplicate the string */
	if (str)
	{
		new_node->str = _strdup(str);
		/* Check if string duplication was successful */
		if (!new_node->str)
		{
			free(new_node); /* Free allocated memory */
			return (NULL); /* return NULL in case of failure */
		}
	}
	/* If the linked list is not empty, find the last node */
	if (node)
	{
		while (node->next)
			/* Append the new node to the end of the linked list */
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node); /* Return a pointer to the new node */
}

/**
 * print_list_str - prints only the str element of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_str(const list_t *h)
{
	size_t i = 0;

	while (h) /* Loop through the linked list */
	{
		_puts(h->str ? h->str : "(nil)"); /* print "(nil)" if it's NULL */
		_puts("\n"); /* Print a newline */
		h = h->next;
		i++;
	}
	/* Return the total number of nodes in the linked list */
	return (i);
}

/**
 * delete_node_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	/* Check if the 'head' pointer is NULL */
	if (!head || !*head)
		return (0);

	/* if index is 0, delete first node */
	if (!index)
	{
		/* Update 'head' to point to the next node */
		node = *head;
		*head = (*head)->next;
		/* free the memory for the string and node */
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node) /* loop through linked list */
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1); /* Return 1 to indicate successful deletion */
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0); /* Return 0 to indicate unsuccessful deletion */
}

/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr; /* Save the original head pointer */
	node = head;
	while (node) /* Loop through the linked list */
	{
		/* Save the 'next' pointer of the current node */
		next_node = node->next;
		/* free memory for the string and current node */
		free(node->str);
		free(node);
		node = next_node;
	}
	/* Update head pointer to NULL to indicate an empty list */
	*head_ptr = NULL;
}
