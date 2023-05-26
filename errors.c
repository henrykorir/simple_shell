#include "shell.h"

/**
 * e_puts - Prints a string to standard error output
 * @str: The string to be printed
 *
 * Return: Nothing
 */

void e_puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		e_putchar(str[i]);
		i++;
	}
}

/**
 * e_putchar - Writes a character to standard error output
 * @c: The character to be printed
 *
 * Return: On success, 1. On error, -1 is returned, and errno is set appropriately.
 */

int e_putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * put_fd - Writes a character to a given file descriptor
 * @c: The character to be written
 * @fd: The file descriptor to write to
 *
 * Return: On success, 1. On error, -1 is returned, and errno is set appropriately.
 */

int put_fd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * puts_fd - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int puts_fd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += put_fd(*str++, fd);
	}
	return (i);
}