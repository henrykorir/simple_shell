#include "shell.h"

/**
 * custom_atoi - Convert a string to an integer.
 * @str: The string to be converted into an integer.
 * Return: The integer value.
 */
int custom_atoi(char *str)
{
unsigned int num = 0, sign = 1, started = 0;

while (*str)
{
if (started && !(*str >= '0' && *str <= '9'))
break;
if (*str == '-')
sign *= -1;
if ((*str >= '0' && *str <= '9'))
{
started = 1;
num = num * 10 + (int)(*str - '0');
}
str++;
}
return (sign * num);
}
