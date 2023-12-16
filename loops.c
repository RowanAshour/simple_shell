#include "new_shell.h"

/**
 * fork_command - forks a an exec thread to run cmd
 * @infoData: the parameter & return info struct
 *
 * Return: void
 */
void fork_command(info_t *infoData)
{
	pid_t childPid;

	childPid = fork();
	if (childPid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (childPid == 0)
	{
		if (execve(infoData->path, infoData->argv, get_environ(infoData)) == -1)
		{
			free_info(infoData, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(infoData->status));
		if (WIFEXITED(infoData->status))
		{
			infoData->status = WEXITSTATUS(infoData->status);
			if (infoData->status == 126)
				print_error(infoData, "Permission denied\n");
		}
	}
}

/**
 * find_builtin - finds a builtin command
 * @infoData: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *          0 if builtin executed successfully,
 *          1 if builtin found but not successful,
 *         -2 if builtin signals exit()
 */
int find_builtin(info_t *infoData)
{
	int i, builtinReturn = -1;
	builtin_table builtintbl[] = {
		{"exit", custom_exit},
		{"env", custom_env},
		{"help", custom_help},
		{"history", custom_history},
		{"setenv", custom_setenv},
		{"unsetenv", custom_unsetenv},
		{"cd", custom_cd},
		{"alias", custom_alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(infoData->argv[0], builtintbl[i].type) == 0)
		{
			infoData->lineCount++;
			builtinReturn = builtintbl[i].func(infoData);
			break;
		}
	return (builtinReturn);
}

/**
 * find_command - finds a command in PATH
 * @infoData: the parameter & return info struct
 *
 * Return: void
 */
void find_command(info_t *infoData)
{
	char *path = NULL;
	int i, nonDelimCount;

	infoData->path = infoData->argv[0];
	if (infoData->lineCountFlag == 1)
	{
		infoData->lineCount++;
		infoData->lineCountFlag = 0;
	}
	for (i = 0, nonDelimCount = 0; infoData->arg[i]; i++)
		if (!is_delim(infoData->arg[i], " \t\n"))
			nonDelimCount++;
	if (!nonDelimCount)
		return;

	path = find_cmd_path(infoData, _getenv(infoData, "PATH="), infoData->argv[0]);
	if (path)
	{
		infoData->path = path;
		fork_command(infoData);
	}
	else
	{
		if ((interactive(infoData) || _getenv(infoData, "PATH=")
			|| infoData->argv[0][0] == '/') && is_cmd(infoData, infoData->argv[0]))
			fork_command(infoData);
		else if (*(infoData->arg) != '\n')
		{
			infoData->status = 127;
			print_error(infoData, "not found\n");
		}
	}
}



/**
 * custom_shell - main shell loop
 * @infoData: the parameter & return info struct
 * @arguments: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int custom_shell(info_t *infoData, char **arguments)
{
	ssize_t readStatus = 0;
	int builtinReturn = 0;

	while (readStatus != -1 && builtinReturn != -2)
	{
		clear_info(infoData);
		if (interactive(infoData))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		readStatus = get_input(infoData);
		if (readStatus != -1)
		{
			set_info(infoData, arguments);
			builtinReturn = find_builtin(infoData);
			if (builtinReturn == -1)
				find_command(infoData);
		}
		else if (interactive(infoData))
			_putchar('\n');
		free_info(infoData, 0);
	}
	write_history(infoData);
	free_info(infoData, 1);
	if (!interactive(infoData) && infoData->status)
		exit(infoData->status);
	if (builtinReturn == -2)
	{
		if (infoData->errNum == -1)
			exit(infoData->status);
		exit(infoData->errNum);
	}
	return (builtinReturn);
}

