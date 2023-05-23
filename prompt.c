#include "shell.h"

/**
 * prompt - print the prompt
 * Return: Nothing
 */
void prompt(void)
{
	write(STDOUT_FILENO, "$ ", 2);
}
