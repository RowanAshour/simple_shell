#include "new_shell.h"

/**
 * custom_realloc - reallocates a block of memory
 * @ptr: pointer to the previous allocated block
 * @old_size: byte size of the previous block
 * @new_size: byte size of the new block
 * Return: pointer to the old block if successful, NULL otherwise.
 */
void *custom_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
    char *new_ptr;

    if (!ptr)
        return malloc(new_size);

    if (!new_size)
        return (free(ptr), NULL);

    if (new_size == old_size)
        return ptr;

    new_ptr = malloc(new_size);
    if (!new_ptr)
        return NULL;

    old_size = old_size < new_size ? old_size : new_size;

    while (old_size--)
        new_ptr[old_size] = ((char *)ptr)[old_size];

    free(ptr);
    return new_ptr;
}

/**
 * free_string_array - frees a string array
 * @str_array: string array to free
 */
void free_string_array(char **str_array)
{
    char **temp = str_array;

    if (!str_array)
        return;

    while (*str_array)
        free(*str_array++);
    free(temp);
}



/**
 * _custom_memset - fills memory with a constant byte
 * @dest: the pointer to the memory area
 * @byte: the byte to fill *dest with
 * @size: the amount of bytes to be filled
 * Return: (dest) a pointer to the memory area dest
 */
char *_custom_memset(char *dest, char byte, unsigned int size)
{
    unsigned int i;

    for (i = 0; i < size; i++)
        dest[i] = byte;
    return dest;
}

