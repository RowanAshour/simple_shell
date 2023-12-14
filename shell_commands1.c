#include "new_shell.h"

/**
 * print_alias_string - Prints an alias string.
 *
 * @node: The alias node.
 *
 * Return: Always 0 on success, 1 on error.
 */
int print_alias_string(list_t *node)
{
	char *p = NULL, *alias_str = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (alias_str = node->str; alias_str <= p; alias_str++)
			_putchar(*alias_str);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}


/**
 * define_alias - Defines alias to a string.
 *
 * @info_data: Parameter struct.
 * @str: The string alias.
 *
 * Return: Always 0 on success, 1 on error.
 */
int define_alias(info_t *info_data, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (remove_alias(info_data, str));

	remove_alias(info_data, str);
	return (add_node_end(&(info_data->alias), str, 0) == NULL);
}

/**
 * display_history - Displays the history list, one command per line, preceded
 *                   with line numbers, starting at 0.
 *
 * @info_data: Structure containing potential arguments.
 *             Used to maintain a constant function prototype.
 * Return: Always 0
 */
int display_history(info_t *info_data)
{
	print_list(info_data->history);
	return (0);
}


/**
 * manage_alias - Mimics the alias builtin (man alias).
 *
 * @info_data: Structure containing potential arguments.
 *             Used to maintain a constant function prototype.
 * Return: Always 0
 */
int manage_alias(info_t *info_data)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info_data->argument_count == 1)
	{
		node = info_data->alias;
		while (node)
		{
			print_alias_string(node);
			node = node->next;
		}
		return (0);
	}

	for (i = 1; info_data->arguments[i]; i++)
	{
		p = _strchr(info_data->arguments[i], '=');
		if (p)
			define_alias(info_data, info_data->arguments[i]);
		else
			print_alias_string(node_starts_with(info_data->alias, info_data->arguments[i], '='));
	}

	return (0);
}

/**
 * remove_alias - Removes alias from a string.
 *
 * @info_data: Parameter struct.
 * @str: The string alias.
 *
 * Return: Always 0 on success, 1 on error.
 */
int remove_alias(info_t *info_data, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info_data->alias),
		get_node_index(info_data->alias, node_starts_with(info_data->alias, str, -1)));
	*p = c;
	return (ret);
}
