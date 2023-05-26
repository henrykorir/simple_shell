#include "shell.h"

/**
 * custom_getline - Read a line of string from a file descriptor.
 * @line: Pointer to store the string.
 * @size: Pointer to store the size of the string.
 * @fd: File descriptor to read from.
 *
 * Return: The length of the string or -1 on failure.
 */
int custom_getline(char **line, size_t *size, int fd)
{
char buffer[BUFFER_SIZE + 1];
int read_size = BUFFER_SIZE, total_size = 0, interactive_mode = isatty(0);
char *tmp;

*line = (char *)_malloc(4);
**line = '\0';

while (read_size == BUFFER_SIZE)
{
if (*line && total_size > 0)
{
if ((*line)[total_size - 1] == '\n' && interactive_mode)
break;
}

read_size = read(fd, buffer, BUFFER_SIZE);

if (read_size < 0 && errno == EINTR)
{
**line = '\n';
*(*line + 1) = '\n';
total_size = 2;
return (total_size);
}

if (read_size < 0)
exit(-1);

if (read_size == 0 && interactive_mode)
return (-1);

tmp = _realloc(*line, total_size + read_size + 4);
*size = total_size + read_size + 4;
*line = tmp;
buffer[read_size] = '\0';
_strcat(*line, buffer);
total_size += read_size;

if (!interactive_mode)
find_and_replace(line, "\n", ";");
}

if (!interactive_mode)
{
tmp = _realloc(*line, _strlen(*line) + 3);
*line = tmp;
(*line)[total_size] = '\n';
(*line)[total_size + 1] = '\0';
}

return (total_size);
}
