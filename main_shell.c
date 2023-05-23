#include "shell.h"

/**
 * main - main program for the simple shell
 * @argc: number of arguments
 * @argv: arguments
 * Return: Last status of the program
 */
int main(int argc __attribute__((unused)), char *argv[])
{
	int ret_status = EXIT_SUCCESS;
	char *line = NULL, **array;
	size_t bufsize = 0;
	int count = 1;

	while (1)
	{
		signal(SIGINT, manage_signal);
		if (isatty(STDIN_FILENO))
			prompt();
		if (getline(&line, &bufsize, stdin) == EOF)
			break;
		array = sp_string(line, " \n\t");
		if (array == NULL || array[0] == NULL)
		{
			/* Print error with perror */
			free(array);
			ret_status = EXIT_FAILURE;
			count++;
			continue;
		}
		if (_strcmp(array[0], "exit") == 0)
			ret_status = exit_cmd(array, argv, line, count, ret_status);
		if (_strcmp(array[0], "env") == 0)
		{
			ret_status = print_env();
			free(array);
			count++;
			continue;
		}
		ret_status = child(array, argv, count);
		free(array);
		array = NULL;
		fflush(stdin); /* Clean the buffer */
		count++;  /* Counter */
	}
	free(line);
	return (ret_status);
}
