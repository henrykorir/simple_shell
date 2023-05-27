#include "shell.h"

/**
 * is_interactive - Check if the shell is in interactive mode
 * @shell_info: Pointer to a struct holding shell information
 *
 * Return: 1 if the shell is in interactive mode, 0 otherwise
 */
int is_interactive(info_t *shell_info)
{
	return (isatty(STDIN_FILENO) && shell_info->read_fd <= 2);
}

/**
 * is_delimiter - checks if a character is a delimiter
 * @c: the character to check
 * @delimiter: the delimiter string
 * Return: 1 if the character is a delimiter, 0 if it is not
 */
int is_delimiter(char c, char *delimiter)
{
	while (*delimiter)
	{
		if (*delimiter++ == c)
			return (1);
	}
	return (0);
}

/**
 * is_alpha - checks if a character is an alphabetic character
 * @c: the character to check
 * Return: 1 if the character is an alphabetic character, 0 otherwise
 */
int is_alpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * convert_to_int - converts a string to an integer
 * @s: the string to be converted
 * Return: the converted integer if at least one digit is found in the
 *          string, otherwise 0 is returned
 */
int convert_to_int(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
