#include "new_shell.h"


/**
 * change_directory - changes the current directory of the process
 * @info_data: Structure containing potential arguments.
 *             Used to maintain a constant function prototype.
 *
 * Return: Always 0
 */
int change_directory(info_t *info_data)
{
	char *current_directory, *target_directory, buffer[1024];
	int chdir_return;

	current_directory = getcwd(buffer, 1024);
	if (!current_directory)
		_puts("TODO: >>getcwd failure emsg here<<\n");

	if (!info_data->arguments[1])
	{
		target_directory = _getenv(info_data, "HOME=");
		if (!target_directory)
			chdir_return = chdir((target_directory = _getenv(info_data, "PWD=")) ? target_directory : "/");
		else
			chdir_return = chdir(target_directory);
	}
	else if (_strcmp(info_data->arguments[1], "-") == 0)
	{
		if (!_getenv(info_data, "OLDPWD="))
		{
			_puts(current_directory);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info_data, "OLDPWD=")), _putchar('\n');
		chdir_return = chdir((target_directory = _getenv(info_data, "OLDPWD=")) ? target_directory : "/");
	}
	else
		chdir_return = chdir(info_data->arguments[1]);

	if (chdir_return == -1)
	{
		print_error(info_data, "can't cd to ");
		_errputs(info_data->arguments[1]), _errputchar('\n');
	}
	else
	{
		_setenv(info_data, "OLDPWD", _getenv(info_data, "PWD="));
		_setenv(info_data, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * display_help - displays help information for the shell
 * @info_data: Structure containing potential arguments.
 *             Used to maintain a constant function prototype.
 *
 * Return: Always 0
 */
int display_help(info_t *info_data)
{
	char **argument_array;

	argument_array = info_data->arguments;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*argument_array); /* temp att_unused workaround */
	return (0);
}


/**
 * exit_shell - exits the shell
 * @info_data: Structure containing potential arguments.
 *             Used to maintain a constant function prototype.
 *
 * Return: Exits with a given exit status (0) if info_data->arguments[0] != "exit"
 */
int exit_shell(info_t *info_data)
{
	int exit_check;

	if (info_data->arguments[1])  /* If there is an exit argument */
	{
		exit_check = error_atoi(info_data->arguments[1]);
		if (exit_check == -1)
		{
			info_data->status = 2;
			print_error(info_data, "Illegal number: ");
			_errputs(info_data->arguments[1]);
			_errputchar('\n');
			return (1);
		}
		info_data->error_number = error_atoi(info_data->arguments[1]);
		return (-2);
	}
	info_data->error_number = -1;
	return (-2);
}
