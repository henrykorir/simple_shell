#include "shell.h"

/**
 * my_history - displays the history list of executed commands
 *              with line numbers starting at 0.
 * @info: structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always returns 0 to indicate successful completion of the function.
 */

int my_history(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - removes an alias from the alias table
 * @info: parameter struct containing potential arguments
 * @str: the string representing the alias to be removed
 *
 * Return: Always returns 0 on success, 1 on error.
 */

int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
							   get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - creates an alias for a given command
 * @info: parameter struct containing potential arguments
 * @str: the string representing the alias and command
 *
 * Return: Always returns 0 on success, 1 on error.
 */

int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints the string value of an alias
 * @node: the node representing the alias to be printed
 *
 * Return: Always returns 0 on success, 1 on error.
 */

int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * my_alias - implements the behavior of the "alias" built-in command (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always returns 0.
 */

int my_alias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->args[i]; i++)
	{
		p = _strchr(info->args[i], '=');
		if (p)
			set_alias(info, info->args[i]);
		else
			print_alias(node_starts_with(info->alias, info->args[i], '='));
	}

	return (0);
}
