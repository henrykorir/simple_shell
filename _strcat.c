#include "shell.h"

/**
 * _strcat - Concatenate two strings.
 * @dest_str: The destination string.
 * @src_str: The source string.
 *
 * Return: Pointer to the concatenated string.
 */
char *_strcat(char *dest_str, char *src_str)
{
char *dest_ptr = dest_str;

while (*dest_ptr)
dest_ptr++;

while (*src_str)
*dest_ptr++ = *src_str++;

*dest_ptr = '\0';

return dest_str;
}
