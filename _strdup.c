#include "shell.h"

/**
 * _strdup - Duplicate a string.
 * @str: The string to be duplicated.
 *
 * Return: The duplicated string.
 */
char *_strdup(char *string)
{
char *duplicate, *copy;

if (!string)
return (NULL);
duplicate = _malloc((_strlen(string) + 1) * sizeof(char));
copy = duplicate;

while (*string)
*copy = *string, string += 1, copy += 1;

*copy = '\0';
return (duplicate);
}
