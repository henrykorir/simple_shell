#include "shell.h"

/**
 * _write - Write to a file descriptor.
 * @fd: File descriptor.
 * @input: String to write.
 * @length: Number of characters in the string.
 *
 * Return: -100 when no queue, 100 when successfully written to.
 */
int _write(int fd, char *input, int length)
{
static char writeQueue[BUFFER_SIZE];
static int queueSize;
int i;

if (fd < 0)
{
queueSize = 0;
return (-100);
}

if (input)
{
if ((length + queueSize) >= BUFFER_SIZE)
{
if (write(fd, writeQueue, BUFFER_SIZE) == -1)
{
print_error(NULL, NULL, "Problem writing");
exit(-1);
}
queueSize = 0;
}

i = 0;
while (i < length)
{
writeQueue[queueSize + i] = input[i];
i++;
}

writeQueue[queueSize + i] = '\0';
queueSize += length;

return (100);
}

if (!input)
{
if (write(fd, writeQueue, queueSize) == -1)
{
print_error(NULL, NULL, "Problem writing");
exit(-1);
}
}

return (0);
}
