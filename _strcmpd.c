#include "shell.h"

/**
 * _strcmpd - Compare a string with a subset.
 * @fstring: The string to compare.
 * @sub: The subset to check.
 *
 * Return: 1 if the subset is found in the string, -1 otherwise.
 */
int _strcmpd(char *fstring, const char *sub)
{
if (!fstring || !sub)
return (-1);
if (!*fstring)
return (-1);
if (_strlen(fstring) < _strlen(sub))
return (-1);
while (*sub)
{
if (*sub == *fstring)
return (1);
sub++;
}
return (-1);
}
