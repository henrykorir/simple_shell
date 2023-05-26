#include "shell.h"

/**
 * get_history_file - Retrieves the path of the history file.
 *
 * @info: The parameter struct.
 *
 * Return: A dynamically allocated string containing the path of the history file.
 */

char *get_history_file(info_t *info)
{
	char *buffer, *directory;

	directory = _getenv(info, "HOME=");
	if (!directory)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(directory) + _strlen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, directory);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);
	return (buffer);
}

/**
 * write_history - Writes command history to a file.
 *
 * @info: The parameter struct.
 *
 * Return: 1 on success, -1 on failure.
 */

int write_history(info_t *info)
{
	ssize_t fileDescriptor;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fileDescriptor = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fileDescriptor == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fileDescriptor);
		_putfd('\n', fileDescriptor);
	}
	_putfd(BUF_FLUSH, fileDescriptor);
	close(fileDescriptor);
	return (1);
}

/**
 * read_history - Reads command history from a file.
 *
 * @info: The parameter struct.
 *
 * Return: The number of history entries read on success (histcount), 0 otherwise.
 */

int read_history(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fileDescriptor, bytesRead, fileSize = 0;
	struct stat st;
	char *buffer = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fileDescriptor = open(filename, O_RDONLY);
	free(filename);
	if (fileDescriptor == -1)
		return (0);
	if (!fstat(fileDescriptor, &st))
		fileSize = st.st_size;
	if (fileSize < 2)
		return (0);
	buffer = malloc(sizeof(char) * (fileSize + 1));
	if (!buffer)
		return (0);
	bytesRead = read(fileDescriptor, buffer, fileSize);
	buffer[fileSize] = 0;
	if (bytesRead <= 0)
		return (free(buffer), 0);
	close(fileDescriptor);
	for (i = 0; i < fileSize; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			build_history_list(info, buffer + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(info, buffer + last, linecount++);
	free(buffer);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history - Adds an entry to a history linked list.
 *
 * @info: The parameter struct.
 * @buffer: The buffer containing the history entry.
 * @linecount: The history line count (histcount).
 *
 * Return: Always 0.
 */

int build_history(info_t *info, char *buffer, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buffer, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renum_history - Renumbers the history linked list after changes.
 *
 * @info: The parameter struct.
 *
 * Return: The new histcount after renumbering.
 */

int renum_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
