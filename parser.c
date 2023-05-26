#include "shell.h"

/**
 * is_cmd - Determines if a file at the specified path is an executable command.
 *
 * @info_struct: a structure containing information about the program's state.
 * @file_path: the path to the file that needs to be checked.
 *
 * Return: 1 if the file is an executable command, 0 otherwise.
 */

int is_cmd(info_t *info_struct, char *file_path)
{
	struct stat st;

	(void)info_struct;
	if (!file_path || stat(file_path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - Duplicates a substring from a string
 * @str: Pointer to a string containing the substring
 * @start: Starting index of the substring to duplicate
 * @stop: Stopping index of the substring to duplicate
 *
 * Return: Pointer to a newly allocated buffer containing the duplicated
 *         substring, or NULL on failure
 */

char *dup_chars(char *str, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (str[i] != ':')
			buf[k++] = str[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_path - Finds a command in the PATH string
 * @info_struct: Pointer to the info struct
 * @path_string: Pointer to the PATH string
 * @command: Pointer to the command to find
 *
 * Return: Pointer to a string containing the full path of the command if
 * found, or NULL if not found
 */

char *find_path(info_t *info_struct, char *path_string, char *command)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!path_string)
		return (NULL);
	if ((_strlen(command) > 2) && starts_with(command, "./"))
	{
		if (is_cmd(info_struct, command))
			return (command);
	}
	while (1)
	{
		if (!path_string[i] || path_string[i] == ':')
		{
			path = dup_chars(path_string, curr_pos, i);
			if (!*path)
				_strcat(path, command);
			else
			{
				_strcat(path, "/");
				_strcat(path, command);
			}
			if (is_cmd(info_struct, path))
				return (path);
			if (!path_string[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
