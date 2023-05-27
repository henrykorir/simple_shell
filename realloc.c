#include "shell.h"

/**
 * _memset - Fills a memory area with a constant byte
 * @mem_area: Pointer to the memory area
 * @byte: Byte to fill *mem_area with
 * @num_bytes: Number of bytes to be filled
 *
 * Return: Pointer to the memory area mem_area
 */

char *_memset(char *mem_area, char byte, unsigned int num_bytes)
{
	unsigned int i;

	for (i = 0; i < num_bytes; i++)
		mem_area[i] = byte;
	return (mem_area);
}

/**
 * ffree - Frees a string of strings
 * @str_array: String of strings
 */

void ffree(char **str_array)
{
	char **arr = str_array;

	if (!str_array)
		return;
	while (*str_array)
		free(*str_array++);
	free(arr);
}

/**
 * _realloc - Reallocates a block of memory
 * @ptr: Pointer to previously allocated block
 * @old_size: Size in bytes of the previous block
 * @new_size: Size in bytes of the new block
 *
 * Return: Pointer to the reallocated block or NULL on failure
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		new_ptr[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (new_ptr);
}
