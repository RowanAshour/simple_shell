#include "new_shell.h"



/**
 * _eputchar - writes the character c to stderr
 * @character: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char character)
{
        static int i;
        static char buf[WRITE_BUF_SIZE];

        if (character == BUF_FLUSH || i >= WRITE_BUF_SIZE)
        {
                write(2, buf, i);
                i = 0;
        }
        if (character != BUF_FLUSH)
                buf[i++] = character;
        return (1);
}



/**
 * _puts_fd - prints an input string
 * @input_str: the string to be printed
 * @fd: the file descriptor to write to
 *
 * Return: the number of characters put
 */
int _puts_fd(char *input_str, int fd)
{
        int count = 0;

        if (!input_str)
                return (0);
        while (*input_str)
        {
                count += _put_fd(*input_str++, fd);
        }
        return (count);
}


/**
 * _eputs - prints an input string
 * @input_str: the string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *input_str)
{
        int index = 0;

        if (!input_str)
                return;
        while (input_str[index] != '\0')
        {
                _eputchar(input_str[index]);
                index++;
        }
}

/**
 * _put_fd - writes the character c to given fd
 * @character: The character to print
 * @fd: The file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _put_fd(char character, int fd)
{
        static int i;
        static char buf[WRITE_BUF_SIZE];

        if (character == BUF_FLUSH || i >= WRITE_BUF_SIZE)
        {
                write(fd, buf, i);
                i = 0;
        }
        if (character != BUF_FLUSH)
                buf[i++] = character;
        return (1);
}                                                                                                     
