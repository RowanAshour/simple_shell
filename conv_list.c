#include "new_shell.h"

/**
 * convert_list_to_strings - Converts a linked list of strings into an array of strings.
 * @head: Pointer to the first node.
 *
 * Return: Array of strings.
 */
char **convert_list_to_strings(list_t *head)
{
	list_t *current = head;
	size_t length = count_nodes(head), index;
	char **strings;
	char *str;

	if (!head || !length)
		return (NULL);

	strings = malloc(sizeof(char *) * (length + 1));

	if (!strings)
		return (NULL);

	for (index = 0; current; current = current->next, index++)
	{
		str = malloc(_strlen(current->str) + 1);

		if (!str)
		{
			for (size_t j = 0; j < index; j++)
				free(strings[j]);

			free(strings);
			return (NULL);
		}

		str = _strcpy(str, current->str);
		strings[index] = str;
	}

	strings[index] = NULL;
	return (strings);
}

/**
 * display_list - Displays the elements of a linked list.
 * @list: Pointer to the first node.
 *
 * Return: Size of the list.
 */
size_t display_list(const list_t *list)
{
	size_t count = 0;

	while (list)
	{
		_puts(convert_number(list->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(list->str ? list->str : "(nil)");
		_puts("\n");
		list = list->next;
		count++;
	}
	return (count);
}


/**
 * find_node_index - Gets the index of a node in a linked list.
 * @head: Pointer to the list head.
 * @node: Pointer to the node.
 *
 * Return: Index of the node or -1 if not found.
 */
ssize_t find_node_index(list_t *head, list_t *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
			return (index);

		head = head->next;
		index++;
	}

	return (-1);
}

/**
 * find_node_with_prefix - Finds the node in a linked list whose string starts with a given prefix.
 * @node: Pointer to the list head.
 * @prefix: String to match.
 * @c: The next character after the prefix to match.
 *
 * Return: Matching node or NULL.
 */
list_t *find_node_with_prefix(list_t *node, char *prefix, char c)
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

