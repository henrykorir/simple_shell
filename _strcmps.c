#include "shell.h"

/**
 * _strcmps - Compare two strings.
 * @fstring: The first string to compare.
 * @sub: The second string to compare.
 *
 * Return: 1 if the strings are equal, -1 otherwise.
 */
int _strcmps(char *fstring, const char *sub)
{
if (!fstring || !sub)
return (-1);
if (!*fstring)
return (-1);
if (_strlen(fstring) < _strlen(sub))
return (-1);
while (*sub && *fstring)
{
if (*sub != *fstring)
return (-1);
sub++, fstring++;
}
return (1);
}
