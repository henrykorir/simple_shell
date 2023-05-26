#include "shell.h"

/**
 * my_exit - exits the shell with a given exit status
 * @info: structure containing potential arguments. Used to maintain
 *        constant function prototype
 * Return: If info->args[0] is "exit", then the function exits the shell
 *         with the given exit status. Otherwise, the function returns 0.
 */
int my_exit(info_t *info)
{
	int exit_check;

	if (info->args[1])
	{
		exit_check = _err_atoi(info->args[1]);
		if (exit_check == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->args[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _err_atoi(info->args[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * my_cd - changes the current working directory of the process
 * @info: structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always returns 0 to indicate successful completion of the function.
 */

int my_cd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->args[1])
	{
		dir = _get_env(info, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = _get_env(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->args[1], "-") == 0)
	{
		if (!_get_env(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_get_env(info, "OLDPWD="));
		_putchar('\n');
		chdir_ret = chdir((dir = _get_env(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->args[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->args[1]);
		_eputchar('\n');
	}
	else
	{
		_set_env(info, "OLDPWD", _get_env(info, "PWD="));
		_set_env(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * my_help - displays help information for shell built-in commands
 * @info: structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always returns 0 to indicate successful completion of the function.
 */

int my_help(info_t *info)
{
	char **arg_array;

	arg_array = info->args;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
}
