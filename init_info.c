#include "shell.h"

/**
 * init_shell_info - initializes shell_info_t struct
 * @shell_info: struct address
 */
void init_shell_info(shell_info_t *shell_info)
{
	shell_info->arguments = NULL;
	shell_info->argument_vector = NULL;
	shell_info->path_string = NULL;
	shell_info->argument_count = 0;
}

/**
 * configure_shell_info - initializes shell_info_t struct
 * @shell_info: struct address
 * @argument_vector: argument vector
 */
void configure_shell_info(shell_info_t *shell_info, char **argument_vector)
{
	int i = 0;

	shell_info->file_name = argument_vector[0];

	if (shell_info->arguments)
	{
		shell_info->argument_vector = strtow(shell_info->arguments, " \t");

		if (!shell_info->argument_vector)
		{
			shell_info->argument_vector = malloc(sizeof(char *) * 2);

			if (shell_info->argument_vector)
			{
				shell_info->argument_vector[0] = _strdup(shell_info->arguments);
				shell_info->argument_vector[1] = NULL;
			}
		}

		for (i = 0; shell_info->argument_vector && shell_info->argument_vector[i]; i++)
			;

		shell_info->argument_count = i;

		replace_alias(shell_info);
		replace_vars(shell_info);
	}
}

/**
 * release_shell_info - frees shell_info_t struct fields
 * @shell_info: struct address
 * @free_all: true if freeing all fields
 */
void release_shell_info(shell_info_t *shell_info, int free_all)
{
	ffree(shell_info->argument_vector);
	shell_info->argument_vector = NULL;
	shell_info->path_string = NULL;

	if (free_all)
	{
		if (!shell_info->command_buffer)
			free(shell_info->arguments);

		if (shell_info->environment)
			free_list(&(shell_info->environment));

		if (shell_info->history_list)
			free_list(&(shell_info->history_list));

		if (shell_info->alias_list)
			free_list(&(shell_info->alias_list));

		ffree(shell_info->environ);
		shell_info->environ = NULL;

		bfree((void **)shell_info->command_buffer);

		if (shell_info->read_file_descriptor > 2)
			close(shell_info->read_file_descriptor);

		_putchar(BUF_FLUSH);
	}
}

