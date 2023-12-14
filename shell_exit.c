#include "new_shell.h"

/**
 **_character_find - locates a character in a string
 *@string: the string to be parsed
 *@character: the character to look for
 *Return: (string) a pointer to the memory area string
 */
char *_character_find(char *string, char character)
{
	do {
		if (*string == character)
			return (string);
	} while (*string++ != '\0');

	return (NULL);
}



/**
 **_string_copy - copies a string
 *@destination: the destination string to be copied to
 *@source: the source string
 *@count: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_string_copy(char *destination, char *source, int count)
{
	int i, j;
	char *result = destination;

	i = 0;
	while (source[i] != '\0' && i < count - 1)
	{
		destination[i] = source[i];
		i++;
	}
	if (i < count)
	{
		j = i;
		while (j < count)
		{
			destination[j] = '\0';
			j++;
		}
	}
	return (result);
}

/**
 **_string_concatenate - concatenates two strings
 *@destination: the first string
 *@source: the second string
 *@count: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_string_concatenate(char *destination, char *source, int count)
{
	int i, j;
	char *result = destination;

	i = 0;
	j = 0;
	while (destination[i] != '\0')
		i++;
	while (source[j] != '\0' && j < count)
	{
		destination[i] = source[j];
		i++;
		j++;
	}
	if (j < count)
		destination[i] = '\0';
	return (result);
}
