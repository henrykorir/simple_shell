#include "shell.h"

/**
 * my_env - prints the current environment variables
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always returns 0.
 */

int my_env(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * get_env - retrieves the value of an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @name: Name of the environment variable to retrieve the value of.
 * Return: The value of the environment variable, or NULL if it does not exist.
 */

char *get_env(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * my_setenv - Initializes a new environment variable or modifies
 *        an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always returns 0.
 */

int my_setenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (set_env(info, info->args[1], info->args[2]))
		return (0);
	return (1);
}

/**
 * my_unsetenv - Removes an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always returns 0.
 */

int my_unsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		unset_env(info, info->args[i]);

	return (0);
}

/**
 * populate_env_list - Populates the environment linked list
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always returns 0.
 */

int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}