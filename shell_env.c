#include "new_shell.h"



/**
 * set_environment - Initialize a new environment variable,
 *                   or modify an existing one
 * @shell_info: Structure containing potential arguments. Used to maintain
 *              constant function prototype.
 *  Return: Always 0
 */
int set_environment(info_t *shell_info, const char *name, const char *value)
{
	char *buffer = NULL;
	list_t *node;
	char *p;

	if (!name || !value)
		return (0);

	buffer = malloc(_strlen(name) + _strlen(value) + 2);
	if (!buffer)
		return (1);

	_strcpy(buffer, name);
	_strcat(buffer, "=");
	_strcat(buffer, value);

	node = shell_info->env;

	while (node)
	{
		p = starts_with(node->str, name);

		if (p && *p == '=')
		{
			free(node->str);
			node->str = buffer;
			return (0);
		}

		node = node->next;
	}

	add_node_end(&(shell_info->env), buffer, 0);
	free(buffer);

	return (0);
}

/**
 * my_environment - prints the current environment
 * @shell_info: Structure containing potential arguments. Used to maintain
 *               constant function prototype.
 * Return: Always 0
 */
int my_environment(info_t *shell_info)
{
	print_list_str(shell_info->env);
	return (0);
}

/**
 * get_environment - gets the value of an environment variable
 * @shell_info: Structure containing potential arguments. Used to maintain
 * @name: environment variable name
 *
 * Return: the value
 */
char *get_environment(info_t *shell_info, const char *name)
{
	list_t *node = shell_info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}
