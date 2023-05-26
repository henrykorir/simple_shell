#include "shell.h"

/**
 * _strlen - Return the length of a string.
 * @string: The string to calculate the length of.
 *
 * Return: The length of the string.
 */
int _strlen(const char *string)
{
int length;

if (!string)
return (0);

length = 0;
while (*string)
{
string += 1;
length += 1;
}

return (length);
}
