#include "shell.h"

/**
 * get_file_path - get PATH
 * @command_name: name of the command
 * Return: a full path of the command or the command name itself on failure
 */
char *get_file_path(char *command_name)
{
	char *path = _getenv("PATH");
	char *full_path = NULL;
	char *tokenized = _strtok(path, ":", 0);
	struct stat fileinfo;

	if (!command_name)
		return (NULL);
	if (*command_name == '/' || *command_name == '.')
	{
		full_path = _malloc(_strlen(command_name) * sizeof(char) + 1);
		_strcpy(full_path, command_name);
		return (full_path);
	}
	while (tokenized)
	{
		full_path = _malloc((_strlen(tokenized) + _strlen(command_name) + 1) * sizeof(char) + 1);
		_strcpy(full_path, tokenized);
		_strcat(full_path, "/");
		_strcat(full_path, command_name);
		if (!stat(full_path, &fileinfo))
			return (full_path);
		free(full_path);
		tokenized = _strtok(NULL, ":", 0);
	}
	full_path = _malloc(_strlen(command_name) * sizeof(char) + 1);
	_strcpy(full_path, command_name);
	return (full_path);
}
