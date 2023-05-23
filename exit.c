#include "shell.h"

/**
 * exit_cmd - function to exit the program
 * @args: array with the command
 * @argv: parameter from main
 * @line: getline buffer to free
 * @prompt_count: count of executes
 * @ret_status: last status to exit
 * Return: status
 */
int exit_cmd(char **args, char *argv[], char *line,
	     int prompt_count, int ret_status)
{
int i = 0, exit_status, is_number;

while (args[i] != NULL)
{
i++;
}

if (i == 1)
{
free(args);
free(line);
exit(ret_status);
}

if (i >= 2)
{
for (i = 0; args[1][i] != '\0'; i++)
{
is_number = _isdigit(args[1][i]);
if (is_number == 0)
{
print_errors(args, argv, prompt_count, 2);
ret_status = 2;
return (ret_status);
}
}

exit_status = _atoi(args[1]);
free(args);
free(line);
exit(exit_status);
}

return (ret_status);
}
