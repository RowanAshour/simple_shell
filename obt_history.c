#include "new_shell.h"

/**
 * read_from_history - Reads history from a file.
 *
 * @info_data: The parameter struct.
 *
 * Return: History count on success, 0 otherwise.
 */
int read_from_history(info_t *info_data)
{
	int i, last = 0, line_count = 0;
	ssize_t file_descriptor, read_length, file_size = 0;
	struct stat st;
	char *buffer = NULL, *filename = obtain_history_file(info_data);

	if (!filename)
		return (0);

	file_descriptor = open(filename, O_RDONLY);
	free(filename);

	if (file_descriptor == -1)
		return (0);

	if (!fstat(file_descriptor, &st))
		file_size = st.st_size;

	if (file_size < 2)
		return (0);

	buffer = malloc(sizeof(char) * (file_size + 1));
	if (!buffer)
		return (0);

	read_length = read(file_descriptor, buffer, file_size);
	buffer[file_size] = 0;

	if (read_length <= 0)
		return (free(buffer), 0);

	close(file_descriptor);

	for (i = 0; i < file_size; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			build_history_list(info_data, buffer + last, line_count++);
			last = i + 1;
		}

	if (last != i)
		build_history_list(info_data, buffer + last, line_count++);

	free(buffer);
	info_data->histcount = line_count;

	while (info_data->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info_data->history), 0);

	renumber_history(info_data);
	return (info_data->histcount);
}

/**
 * write_to_history - Creates a file or appends to an existing file.
 *
 * @info_data: The parameter struct.
 *
 * Return: 1 on success, else -1.
 */
int write_to_history(info_t *info_data)
{
	ssize_t file_descriptor;
	char *filename = obtain_history_file(info_data);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	file_descriptor = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);

	if (file_descriptor == -1)
		return (-1);

	for (node = info_data->history; node; node = node->next)
	{
		_putsfd(node->str, file_descriptor);
		_putfd('\n', file_descriptor);
	}
	_putfd(BUF_FLUSH, file_descriptor);
	close(file_descriptor);
	return (1);
}



/**
 * build_history_list - Adds entry to a history linked list.
 *
 * @info_data: Structure containing potential arguments. Used to maintain
 * @buffer: Buffer.
 * @line_count: The history line count, histcount.
 *
 * Return: Always 0.
 */
int build_history_list(info_t *info_data, char *buffer, int line_count)
{
	list_t *node = NULL;

	if (info_data->history)
		node = info_data->history;

	add_node_end(&node, buffer, line_count);

	if (!info_data->history)
		info_data->history = node;

	return (0);
}

/**
 * renumber_history - Renumbers the history linked list after changes.
 *
 * @info_data: Structure containing potential arguments. Used to maintain
 *
 * Return: The new histcount.
 */
int renumber_history(info_t *info_data)
{
	list_t *node = info_data->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}

	return (info_data->histcount = i);
}

/**
 * obtain_history_file - Obtains the history file.
 *
 * @info_data: Parameter struct.
 *
 * Return: Allocated string containing history file.
 */
char *obtain_history_file(info_t *info_data)
{
	char *buffer, *directory;

	directory = _getenv(info_data, "HOME=");
	if (!directory)
		return (NULL);

	buffer = malloc(sizeof(char) * (_strlen(directory) + _strlen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);

	buffer[0] = 0;
	_strcpy(buffer, directory);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);
	return (buffer);
}
