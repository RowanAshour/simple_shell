#include "new_shell.h"

/**
 * set_environment_variable - Initializes a new environment variable,
 * or modifies an existing one.
 *
 * @info_data: Structure containing potential arguments.
 *             Used to maintain constant function prototype.
 * @variable: The string env var property.
 * @value: The string env var value.
 *
 * Return: Always 0.
 */
int set_environment_variable(info_t *info_data, char *variable, char *value)
{
	char *buffer = NULL;
	list_t *node;
	char *p;

	if (!variable || !value)
		return (0);

	buffer = malloc(_strlen(variable) + _strlen(value) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, variable);
	_strcat(buffer, "=");
	_strcat(buffer, value);
	node = info_data->env;
	while (node)
	{
		p = starts_with(node->str, variable);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buffer;
			info_data->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info_data->env), buffer, 0);
	free(buffer);
	info_data->env_changed = 1;
	return (0);
}

/**
 * remove_environment_variable - Removes an environment variable.
 *
 * @info_data: Structure containing potential arguments.
 *             Used to maintain constant function prototype.
 * @variable: The string env var property.
 *
 * Return: 1 on delete, 0 otherwise.
 */
int remove_environment_variable(info_t *info_data, char *variable)
{
	list_t *node = info_data->env;
	size_t i = 0;
	char *p;

	if (!node || !variable)
		return (0);

	while (node)
	{
		p = starts_with(node->str, variable);
		if (p && *p == '=')
		{
			info_data->env_changed = delete_node_at_index(&(info_data->env), i);
			i = 0;
			node = info_data->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info_data->env_changed);
}



/**
 * fetch_environment - Returns the string array copy of our environment.
 *
 * @info_data: Structure containing potential arguments.
 *             Used to maintain constant function prototype.
 *
 * Return: Always 0.
 */
char **fetch_environment(info_t *info_data)
{
	if (!info_data->environ || info_data->env_changed)
	{
		info_data->environ = list_to_strings(info_data->env);
		info_data->env_changed = 0;
	}

	return (info_data->environ);
}
