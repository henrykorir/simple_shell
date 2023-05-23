#include "shell.h"

/**
 * child - creates the child process
 * @args: array of argument strings passed to the new program
 * @argv: array arguments from main
 * @prompt_count: count of the number of times the program is called
 * Return: return the child's exit status.
 */
int child(char **args, char *argv[], int prompt_count)
{
    int exit_status, status;
    struct stat buffer;
    pid_t child_pid;

    if (args == NULL || args[0] == NULL)
        return (EXIT_SUCCESS);

    if (stat(args[0], &buffer) == -1)
    {
        print_errors(args, argv, prompt_count, 127);
        return (127);
    }
    if (access(args[0], X_OK) == -1)
    {
        print_errors(args, argv, prompt_count, 126);
        return (126);
    }

    child_pid = fork();

    if (child_pid == 0)
    {
        exit_status = execve(args[0], args, environ);
    }
    else
    {
        wait(&status);
        exit_status = WEXITSTATUS(status);
    }
    return (exit_status);
}
