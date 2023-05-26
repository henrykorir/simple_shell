#include "shell.h"

/**
 * print_shell_errors - print errors of the program
 * @cmd_array: array of command and arguments
 * @av: array from main
 * @prompt_count: count the number of prompts
 * @error_num: indicates the error
 * Return: Nothing
 */
void print_shell_errors(char **cmd_array, char *av[], int prompt_count, int error_num)
{
	int av_len, cmd_array_len;

	cmd_array_len = _strlen(cmd_array[0]);
	av_len = _strlen(av[0]);

	if (error_num == 127 || error_num == 126)
	{
		write(STDOUT_FILENO, av[0], av_len);
		write(STDOUT_FILENO, " : ", 3);
		print_integer(prompt_count);
		write(STDOUT_FILENO, ": ", 2);
		write(STDOUT_FILENO, cmd_array[0], cmd_array_len);
		write(STDOUT_FILENO, ": ", 2);
		perror("");
	}

	if (error_num == 2)
	{
		write(STDOUT_FILENO, av[0], av_len);
		write(STDOUT_FILENO, ": ", 2);
	}
}

/**
 * print_integer - print an integer using recursion
 * @n: number to print
 * Return: length of the number
 */
int print_integer(int n)
{
	int count = 1;

	return (recursion_int(n, count));
}

/**
 * recursion_int - recursively print an integer
 * @n: the number to print
 * @count: count the length of the number
 * Return: amount of digits of the number n
 */
int recursion_int(int n, int count)
{
	unsigned int num;

	if (n < 0)
	{
		_putchar('-');
		num = (-1) * n;
		count++;
	}
	else
		num = n;

	if (num / 10)
	{
		count = recursion_int(num / 10, count + 1);
	}

	_putchar((num % 10) + '0');
	return (count);
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(STDOUT_FILENO, &c, 1));
}
