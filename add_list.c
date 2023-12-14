#include "new_shell.h"

/**
 * add_node_to_end - Adds a new node to the end of the list.
 *
 * @head: Address of pointer to the head node.
 * @data: Data field of the new node.
 * @index: Index used by history for the new node.
 *
 * Return: Pointer to the new node.
 */
list_t *add_node_to_end(list_t **head, const char *data, int index)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	/* Allocate memory for the new node */
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);

	/* Initialize the new node */
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->index = index;

	/* Copy data if provided */
	if (data)
	{
		new_node->data = _strdup(data);
		if (!new_node->data)
		{
			free(new_node);
			return (NULL);
		}
	}

	/* Update the list */
	node = *head;
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;

	return (new_node);
}


/**
 * add_node_to_start - Adds a new node to the start of the list.
 *
 * @head: Address of pointer to the head node.
 * @data: Data field of the new node.
 * @index: Index used by history for the new node.
 *
 * Return: Pointer to the new head of the list.
 */
list_t *add_node_to_start(list_t **head, const char *data, int index)
{
	list_t *new_head;

	if (!head)
		return (NULL);

	/* Allocate memory for the new node */
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);

	/* Initialize the new node */
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->index = index;

	/* Copy data if provided */
	if (data)
	{
		new_head->data = _strdup(data);
		if (!new_head->data)
		{
			free(new_head);
			return (NULL);
		}
	}

	/* Update the list */
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}



/**
 * delete_node_at_index - Deletes a node at the given index.
 *
 * @head: Address of pointer to the first node.
 * @index: Index of the node to delete.
 *
 * Return: 1 on success, 0 on failure.
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	/* Delete the first node if index is 0 */
	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->data);
		free(node);
		return (1);
	}

	/* Traverse the list to find the node at the specified index */
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->data);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}

	return (0);
}

/**
 * free_list_nodes - Frees all nodes of a list.
 *
 * @head: Address of pointer to the head node.
 *
 * Return: Void.
 */
void free_list_nodes(list_t **head)
{
	list_t *node, *next_node, *current_head;

	if (!head || !*head)
		return;

	/* Free each node in the list */
	current_head = *head;
	node = current_head;
	while (node)
	{
		next_node = node->next;
		free(node->data);
		free(node);
		node = next_node;
	}

	*head = NULL;
}

/**
 * print_data_only - Prints only the data element of a list_t linked list.
 *
 * @node: Pointer to the first node.
 *
 * Return: Size of the list.
 */
size_t print_data_only(const list_t *node)
{
	size_t count = 0;

	while (node)
	{
		/* Print the data or "(nil)" if data is NULL */
		_puts(node->data ? node->data : "(nil)");
		_puts("\n");
		node = node->next;
		count++;
	}

	return (count);
}
