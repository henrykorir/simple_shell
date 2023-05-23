#include "shell.h"

/**
 * _strdup - Function that copies a string
 * @str: pointer that points to the address of the string to be copied
 * Return: pointer to the duplicated string or NULL if it fails
 */
char *_strdup(const char *str)
{
int i, size;
char *dup;

if (str == NULL)
return (NULL);

for (i = 0; str[i] != '\0'; i++)
{
}
size = i;

dup = malloc(sizeof(char) * (size + 1));

if (dup == NULL)
return (NULL);

for (i = 0; i < size; i++)
dup[i] = str[i];
dup[i] = '\0';

return (dup);
}

/**
 * _strlen - return the length of a string
 * @str: pointer to a string
 * Return: the length of the string
 */
int _strlen(char *str)
{
int i;

for (i = 0; str[i] != '\0'; i++)
{
}
return (i);
}

/**
 * _atoi - Convert a string to an integer.
 * @s: The string to be converted into an integer
 * Return: The converted integer
 */
int _atoi(char *s)
{
int sign = 1, i = 0;
unsigned int num = 0;

while (s[i])
{
if (s[i] == '-')
sign *= -1;

while (s[i] >= '0' && s[i] <= '9')
{
num = (num * 10) + (s[i] - '0');
i++;
}
if (num != 0)
break;

i++;
}

num *= sign;
return (num);
}

/**
 * _isdigit - function that checks for a digit 0 through 9
 * @c: character to check
 * Return: 1 if c is a digit, 0 otherwise
 */
int _isdigit(int c)
{
if (c >= '0' && c <= '9')
{
return (1);
}
else
{
return (0);
}
}

/**
 * manage_signal - function to manage the signal CTRL + C
 * @num_signal: number for the signal received
 * Return: None
 */
void manage_signal(int num_signal __attribute__((unused)))
{
_putchar('\n');
prompt();
}
