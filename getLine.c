#include "shell.h"

/**
 * input_buf - Buffers chained commands from input.
 *
 * @info: A pointer to the parameter struct containing relevant information.
 * @buffer: The address of the buffer to store the input.
 * @length: The address of the variable to store the length of the input.
 *
 * Return: The number of bytes read from input.
 */

ssize_t input_buf(info_t *info, char **buffer, size_t *length)
{
	ssize_t bytesRead = 0;
	size_t lengthRead = 0;

	if (!*length)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		bytesRead = getline(buffer, &lengthRead, stdin);
#else
		bytesRead = _getline(info, buffer, &lengthRead);
#endif
		if (bytesRead > 0)
		{
			if ((*buffer)[bytesRead - 1] == '\n')
			{
				(*buffer)[bytesRead - 1] = '\0';
				bytesRead--;
			}
			info->linecount_flag = 1;
			remove_comments(*buffer);
			build_history_list(info, *buffer, info->histcount++);
			{
				*length = bytesRead;
				info->cmd_buf = buffer;
			}
		}
	}
	return (bytesRead);
}

/**
 * get_input - Reads a line of input from user, excluding the newline character.
 *
 * @info: A pointer to the parameter struct containing relevant information.
 *
 * Return: The number of bytes read from input.
 */

ssize_t get_input(info_t *info)
{
	static char *buffer;
	static size_t i, j, length;
	ssize_t bytesRead = 0;
	char **bufferPointer = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	bytesRead = input_buf(info, &buffer, &length);
	if (bytesRead == -1)
		return (-1);
	if (length)
	{
		j = i;
		p = buffer + i;

		check_chain(info, buffer, &j, i, length);
		while (j < length)
		{
			if (is_chain(info, buffer, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= length)
		{
			i = length = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*bufferPointer = p;
		return (_strlen(p));
	}

	*bufferPointer = buffer;
	return (bytesRead);
}

/**
 * read_buf - Reads data from a buffer into a provided buffer.
 *
 * @info: A pointer to the parameter struct containing relevant information.
 * @buf: The buffer to read data into.
 * @i: The size of the buffer.
 *
 * Return: The number of bytes read.
 */

ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t bytesRead = 0;

	if (*i)
		return (0);
	bytesRead = read(info->readfd, buf, READ_BUF_SIZE);
	if (bytesRead >= 0)
		*i = bytesRead;
	return (bytesRead);
}

/**
 * _getline - Reads the next line of input from STDIN.
 *
 * @info: A pointer to the parameter struct containing relevant information.
 * @ptr: A pointer to the address of the buffer, which may be preallocated or NULL.
 * @length: The size of the preallocated buffer, if not NULL.
 *
 * Return: The line of input, read as a string, or NULL on failure.
 */

int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - Signal handler function to block the SIGINT signal (Ctrl-C).
 *
 * @sig_num: The signal number of the received signal.
 *
 * Return: void
 */

void sigintHandler(__attribute__((unused)) int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
