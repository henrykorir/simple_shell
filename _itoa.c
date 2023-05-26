#include "shell.h"

/**
 * itoa - Convert an integer to a string.
 * @n: The number to convert.
 *
 * Return: The string representation of the number.
 */
char *itoa(int n)
{
int length, j, k, digit, tmp, i = 0;
unsigned int num;
char *str = _malloc(num_len((n > 0) ? n : -1 * n) + 2);

if (!str)
return (NULL);

if (n < 0)
n *= -1, *(str + i) = '-', i++;

num = n;
length = num_len(num);
j = length - 1;

if (num == 0)
nums[i] = '0', i++;
else
{
while (j >= 0)
{
if (num % pow_b(10, j) == 0 && j != 0)
{
str[i] = '0' + num / pow_b(10, j);
i++;

for (k = j; k > 0; k--)
str[i] = '0', i++;

j = -1;
}
else
{
digit = num / pow_b(10, j);
str[i] = '0' + digit;
i++;

tmp = num;
num -= pow_b(10, j) * digit;

if (num_len(tmp) - num_len(num) == 2)
str[i] = '0', i++, j--;

j--;
}
}
}

return (str);
}
