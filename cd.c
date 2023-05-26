#include "shell.h"

/**
 * change_directory - change current directory
 * @path: new path
 * Return: 0 on success and 1 on failure
 */

int change_directory(char *path)
{
	int status, exit_status = 0;
	char *current_dir = _getenv("PWD");
	char *buf = NULL, *cdir, *msg;
	char *smn;
	size_t size = 0;

	if (!path || !_strcmp(path, "~"))
		status = chdir(_getenv("HOME"));
	else if (!_strcmp(path, "-"))
		status = chdir(_getenv("OLDPWD"));
	else
		status = chdir(path);

	if (status < 0)
	{
		errno = -3;
		msg = _malloc(_strlen("No such file or directory ") + _strlen(path) + 4);
		_strcpy(msg, "No such file or directory ");
		smn = _malloc(_strlen("cd: ") + _strlen(path) + 4);
		_strcpy(smn, "cd: "), _strcat(smn, path);
		print_error(smn, NULL, msg);
		free(msg), free(smn);
		exit_status = 1;
	}

	_setenv("OLDPWD", current_dir, 1);
	cdir = getcwd(buf, size);
	_setenv("PWD", cdir, 1);
	free(buf), free(cdir);
	return (exit_status);
}
