#include "new_shell.h"



/**
 * custom_strdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *custom_strdup(const char *str)
{
	int length = 0;
	char *result;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	result = malloc(sizeof(char) * (length + 1));
	if (!result)
		return (NULL);
	for (length++; length--;)
		result[length] = *--str;
	return (result);
}

/**
 * custom_puts - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void custom_puts(char *str)
{
	int index = 0;

	if (!str)
		return;
	while (str[index] != '\0')
	{
		custom_putchar(str[index]);
		index++;
	}
}

/**
 * custom_strcpy - copies a string
 * @destination: the destination
 * @source: the source
 *
 * Return: pointer to destination
 */
char *custom_strcpy(char *destination, char *source)
{
	int index = 0;

	if (destination == source || source == 0)
		return (destination);
	while (source[index])
	{
		destination[index] = source[index];
		index++;
	}
	destination[index] = 0;
	return (destination);
}

/**
 * custom_putchar - writes the character c to stdout
 * @character: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int custom_putchar(char character)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (character == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (character != BUF_FLUSH)
		buf[i++] = character;
	return (1);
}

