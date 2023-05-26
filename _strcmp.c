#include "shell.h"

/**
 * _strcmp - Compare two strings.
 * @str1: The first string.
 * @str2: The second string.
 *
 * Return: 0 if the strings are equal, a negative value if str1 is less than str2,
 *         or a positive value if str1 is greater than str2.
 */
int _strcmp(char *str1, char *str2)
{
if (!str1 && str2)
return (-1);
if (!str2 && str1)
return (-1);

while (*str1)
{
if (*str1 != *str2)
break;
str1++, str2++;
}

return (*(unsigned char *)str1 - *(unsigned char *)str2);
}
