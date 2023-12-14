#include "new_shell.h"

/**
 * get_input - Gets a line minus the newline.
 *
 * @info_data: Parameter struct.
 *
 * Return: Bytes read.
 */
ssize_t get_input(info_t *info_data)
{
	static char *buffer;
	static size_t buffer_start, buffer_end, buffer_length;
	ssize_t read_bytes = 0;
	char **buffer_ptr = &(info_data->arg), *position;

	_putchar(BUF_FLUSH);
	read_bytes = buffer_input(info_data, &buffer, &buffer_length);
	if (read_bytes == -1)
		return -1;
	if (buffer_length)
	{
		buffer_end = buffer_start;
		position = buffer + buffer_start;

		check_chain(info_data, buffer, &buffer_end, buffer_start, buffer_length);
		while (buffer_end < buffer_length)
		{
			if (is_chain(info_data, buffer, &buffer_end))
				break;
			buffer_end++;
		}

		buffer_start = buffer_end + 1;
		if (buffer_start >= buffer_length)
		{
			buffer_start = buffer_length = 0;
			info_data->cmd_buf_type = CMD_NORM;
		}

		*buffer_ptr = position;
		return _strlen(position);
	}

	*buffer_ptr = buffer;
	return read_bytes;
}

/**
 * _getline - Gets the next line of input from STDIN.
 *
 * @info_data: Parameter struct.
 * @ptr: Address of pointer to buffer, preallocated or NULL.
 * @length: Size of preallocated ptr buffer if not NULL.
 *
 * Return: Size.
 */
int _getline(info_t *info_data, char **ptr, size_t *length)
{
	static char buffer[READ_BUF_SIZE];
	static size_t buffer_start, buffer_length;
	size_t k;
	ssize_t read_bytes = 0, size = 0;
	char *position = NULL, *new_position = NULL, *c;

	position = *ptr;
	if (position && length)
		size = *length;
	if (buffer_start == buffer_length)
		buffer_start = buffer_length = 0;

	read_bytes = read_buffer(info_data, buffer, &buffer_length);
	if (read_bytes == -1 || (read_bytes == 0 && buffer_length == 0))
		return -1;

	c = _strchr(buffer + buffer_start, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : buffer_length;
	new_position = _realloc(position, size, size ? size + k : k + 1);
	if (!new_position)
		return position ? free(position), -1 : -1;

	if (size)
		_strncat(new_position, buffer + buffer_start, k - buffer_start);
	else
		_strncpy(new_position, buffer + buffer_start, k - buffer_start + 1);

	size += k - buffer_start;
	buffer_start = k;
	position = new_position;

	if (length)
		*length = size;
	*ptr = position;
	return size;
}

/**
 * read_buffer - Reads a buffer.
 *
 * @info_data: Parameter struct.
 * @buffer: Buffer.
 * @position: Size.
 *
 * Return: Read bytes.
 */
ssize_t read_buffer(info_t *info_data, char *buffer, size_t *position)
{
	ssize_t read_bytes = 0;

	if (*position)
		return 0;
	read_bytes = read(info_data->read_fd, buffer, READ_BUF_SIZE);
	if (read_bytes >= 0)
		*position = read_bytes;
	return read_bytes;
}

/**
 * handle_sigint - Blocks ctrl-C.
 *
 * @sig_num: The signal number.
 *
 * Return: Void.
 */
void handle_sigint(__attribute__((unused)) int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

/**
 * buffer_input - Buffers chained commands.
 *
 * @info_data: Parameter struct.
 * @buffer: Address of the buffer.
 * @length: Address of the length variable.
 *
 * Return: Bytes read.
 */
ssize_t buffer_input(info_t *info_data, char **buffer, size_t *length)
{
	ssize_t read_bytes = 0;
	size_t len_position = 0;

	if (!*length)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, handle_sigint);
#if USE_GETLINE
		read_bytes = getline(buffer, &len_position, stdin);
#else
		read_bytes = _getline(info_data, buffer, &len_position);
#endif
		if (read_bytes > 0)
		{
			if ((*buffer)[read_bytes - 1] == '\n')
			{
				(*buffer)[read_bytes - 1] = '\0';
				read_bytes--;
			}
			info_data->linecount_flag = 1;
			remove_comments(*buffer);
			build_history_list(info_data, *buffer, info_data->histcount++);
			{
				*length = read_bytes;
				info_data->cmd_buffer = buffer;
			}
		}
	}
	return (read_bytes);
}

