#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>

#define TRUE 1
/**
 * __mem_alloc - tries to allocate requested memory
 * @lineptr: memory pointer
 * @n: the size of memory requested
 * Return: the true size of the memory successfully allocated
 */
size_t  __mem_alloc(char **lineptr, size_t n)
{
	size_t size = n + 1024;

	if (lineptr == NULL || *lineptr == NULL)
	{
		*lineptr = malloc(size * sizeof(char));
		if (*lineptr == NULL)
			return (0);
	}
	else
	{
		*lineptr = realloc(*lineptr, (size * sizeof(char)));
		if (*lineptr == NULL)
			return (n);
	}
	return (size);
}
/**
 * _getline - reads characters from a file descriptor
 * @lineptr: the character buffer
 * @n: size of the buffer
 * @fd: file descriptor
 * Return: total number of bytes read
 */
ssize_t _getline(char **lineptr, size_t *n, int fd)
{
	static ssize_t n_chars;
	int nb_read;
	size_t nbytes = 0;

	nbytes = __mem_alloc(lineptr, (*n));
	if (nbytes == 0)
		return (0);
	if (nbytes == *n)
		return (*n);
	*n = nbytes;
	nb_read = read(fd, *lineptr, (*n));
	if (nb_read < 0 && *lineptr != NULL && n_chars == 0)
	{
		perror("read");
		free(*lineptr);
		return (EXIT_FAILURE);
	}
	if (nb_read > 0)
		n_chars += nb_read;
	(*lineptr)[nb_read - 1] = '\0';
	return (n_chars);
}
/**
 * parse_commands - creates a 2D array of command line
 * @line: command line string
 * @cmds: final 2D array of command and arguments
 * Return: size of the 2D array.
 */
int parse_commands(char *line, char ***cmds)
{
	char *token = NULL;
	int i = 0;

	token = strtok(line, " ");
	while (token != NULL)
	{
		puts(token);
		*cmds = realloc(*cmds, (i + 2) * sizeof(char *));
		(*cmds)[i] = strdup(token);
		token = strtok(NULL, " ");
		i++;
	}

	return (i);
}
/**
 * process_command - reads and parses input
 * @commands: commands
 * Return: number of commands
 */
int process_command(char ***commands)
{
	char *line = NULL, *prompt = "#cisfun$ ";
	size_t n = 0;
	ssize_t nb_read = 0;

	if (isatty(STDIN_FILENO) == 1)
		write(STDOUT_FILENO, prompt, strlen(prompt) + 1);
	nb_read = _getline(&line, &n, STDIN_FILENO);
	if (nb_read < 0)
	{
		perror("_getline");
		return (0);
	}
	if (line[0] == '"' && line[strlen(line) - 1] == '"')
	{
		line[strlen(line) - 1] = '\0';
		strcpy(line, line + 1);
	}

	return (parse_commands(line, commands));
}
/**
 * main - Entry point.
 * @argc: number of arguments
 * @argv: pointer to command lines
 * @envp: environment pointer
 * Return: 0 on success or an integer that is not 0
 * on error
 */
int main(int argc __attribute__((unused)),
char *argv[] __attribute__((unused)),
char *envp[] __attribute__((unused)))
{
	char **cmds = NULL;
	int status, n;
	pid_t cpid, w;
	struct stat st;

	while (TRUE)
	{
		cmds = NULL;
		n = process_command(&cmds);
		if (n > 0 && (cmds[0] != NULL || strlen(cmds[0]) != 0))
		{
			n = stat(cmds[0], &st);
			if (n == 0)
			{
				cpid = fork();
				if (cpid != 0)
				{
					w = waitpid(cpid, &status, 0);
					if (w == -1)
					{
						perror("waitpid");
						exit(EXIT_FAILURE);
					}
				}
				else
				{
					execve(cmds[0], cmds, envp);
					perror(argv[0]);
					_exit(EXIT_FAILURE);
				}
			}
			else
				perror(argv[0]);
		}
		if (isatty(STDIN_FILENO) == 0)
			break;
	}
	return (0);
}
