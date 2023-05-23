#include "shell.h"

/**
 * print_errors - prints errors of the program
 * @args: array of command and arguments
 * @argv: array from main
 * @prompt_count: count of the number prompts
 * @error_num: indicates the error
 *
 * Return: Nothing
 */
void print_errors(char **args, char *argv[], int prompt_count, int error_num)
{
    int argv_len, args_len;

    args_len = _strlen(args[0]);
    argv_len = _strlen(argv[0]);

    if (error_num == 127 || error_num == 126)
    {
        write(STDOUT_FILENO, argv[0], argv_len);
        write(STDOUT_FILENO, " : ", 3);
        print_integer(prompt_count);
        write(STDOUT_FILENO, ": ", 2);
        write(STDOUT_FILENO, args[0], args_len);
        write(STDOUT_FILENO, ": ", 2);
        perror("");
    }

    if (error_num == 2)
    {
        write(STDOUT_FILENO, argv[0], argv_len);
        write(STDOUT_FILENO, ": ", 2);
    }
}

/**
 * print_integer - calls a recursive function with an iterator
 * @num: number to print
 *
 * Return: length of the number
 */
int print_integer(int num)
{
    int iterator = 1;

    return (recursion_int(num, iterator));
}

/**
 * recursion_int - recursive function to print an integer
 * @num: receive a number
 * @count: count the length of the number
 *
 * Return: Amount of digits of the number 'num'
 */
int recursion_int(int num, int count)
{
    unsigned int number;

    if (num < 0)
    {
        _putchar('-');
        number = (-1) * num;
        count++;
    }
    else
        number = num;

    if (number / 10)
    {
        count = recursion_int(number / 10, count = count + 1);
    }

    _putchar((number % 10) + '0');
    return (count);
}

/**
 * _putchar - writes the character 'c' to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
    return (write(STDOUT_FILENO, &c, 1));
}
