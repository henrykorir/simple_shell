#include "shell.h"

/**
 * _strcpy - Copy a string.
 * @dest: The destination string.
 * @src: The source string.
 *
 * Return: Pointer to the destination string.
 */
char *_strcpy(char *destination, char *source)
{
char *ptr = destination;

if (!destination)
return (NULL);
while (*source)
*destination++ = *source++;
*destination = '\0';
return (ptr);
}
