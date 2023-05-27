#include "shell.h"

/**
 * freee - frees a pointer and sets its address to NULL.
 *
 * @pointer: a pointer to the pointer to be freed.
 *
 * Return: 1 if the pointer was successfully freed, 0 otherwise.
 */
int freee(void **pointer)
{
	if (pointer && *pointer)
	{
		free(*pointer);
		*pointer = NULL;
		return (1);
	}
	return (0);
}
