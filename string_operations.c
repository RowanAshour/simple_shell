#include "new_shell.h"

/**
 * convert_to_integer - Converts a string to an integer.
 *
 * @str: The string to be converted.
 *
 * Return: 0 if no numbers in string, converted number otherwise.
 */
int convert_to_integer(char *str)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; str[i] != '\0' && flag != 2; i++)
	{
		if (str[i] == '-')
			sign *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (str[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

/**
 * is_alphabetic - Checks for an alphabetic character.
 *
 * @character: The character to check.
 *
 * Return: 1 if character is alphabetic, 0 otherwise.
 */
int is_alphabetic(int character)
{
	if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z'))
		return (1);
	else
		return (0);
}



/**
 * check_interactive - Returns true if the shell is in interactive mode.
 *
 * @info_data: Struct address.
 *
 * Return: 1 if in interactive mode, 0 otherwise.
 */
int check_interactive(info_t *info_data)
{
	return (isatty(STDIN_FILENO) && info_data->read_file_descriptor <= 2);
}

/**
 * is_separator - Checks if a character is a separator.
 *
 * @character: The char to check.
 * @separator_str: The separator string.
 *
 * Return: 1 if true, 0 if false.
 */
int is_separator(char character, char *separator_str)
{
	while (*separator_str)
		if (*separator_str++ == character)
			return (1);
	return (0);
}
