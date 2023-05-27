#include "shell.h"

/**
 * err_atoi - Convert a string to an integer
 *
 * @s: The string to be converted
 *
 * Return: The converted number if there are numbers in the string,
 *         0 otherwise. Returns -1 on error.
 */

int err_atoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - Prints an error message with specified error type.
 *
 * @info: A struct containing information about the parameter and return values.
 * @estr: A string containing the specified error type.
 *
 * Return: Returns 0 on success, and -1 on error.
 */

void print_error(info_t *info, char *estr)
{
	e_puts(info->fname);
	e_puts(": ");
	print_decimal(info->line_count, STDERR_FILENO);
	e_puts(": ");
	e_puts(info->argv[0]);
	e_puts(": ");
	e_puts(estr);
}

/**
 * print_decimal - Prints a decimal (integer) number in base 10.
 *
 * @input: The integer to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters printed.
 */

int print_decimal(int input, int fd)
{
	int (*__putchar)(char) = putchar_fd;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = e_putchar_fd;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - Converts a number to a string representation in the specified base.
 *
 * @num: The number to be converted.
 * @base: The base to use for the conversion.
 * @flags: Flags to modify the behavior of the conversion.
 *
 * Return: A string representation of the converted number.
 */

char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do
	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - Replaces the first instance of '#' character with '\0'.
 *
 * @buf: The address of the string to be modified.
 *
 * Return: Always returns 0.
 */

void remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
