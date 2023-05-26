#include "shell.h"
#include "error.h"

/**
 * print_error - Print an error message.
 * @program: Command.
 * @cmds_run: Pointer to the number of commands run.
 * @message: Error message.
 *
 * Return: None.
 */
void print_error(char *program, int *cmds_run, char *message)
{
char *num_cmds;
static int *commands_run;
static char *program_name;

if (!message)
{
commands_run =  cmds_run;
program_name = program;
return;
}

if (!cmds_run || !program)
{
_write(-1, NULL, 0);
_write(2, program_name, _strlen(program_name) + 1);
_write(2, ": ", 2);
num_cmds = itoa(*commands_run);
_write(2, num_cmds, _strlen(num_cmds));
free(num_cmds);
_write(2, ": ", 2);
_write(2, program, _strlen(program));
_write(2, ": ", 2);
_write(2, message, _strlen(message));
_write(2, "\n", 1);
_write(2, NULL, 0);
}
}
