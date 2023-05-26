#include "shell.h"

/**
 * add_alias - Add a node to the linked list.
 * @head: Pointer to the first node.
 * @key: Key to add in the node.
 * @value: Value to be added with the key.
 *
 * Return: 0 on success, -1 on failure.
 */
int add_alias(alias **head, char *key, char *value)
{
	alias *new_node, *current_node;

	if (!head)
		return (-1);

	new_node = _malloc(sizeof(alias));
	new_node->key = _strdup(key);
	new_node->value = _strdup(value);
	new_node->next = NULL;

	if (!*head)
	{
		*head = new_node;
		return (0);
	}

	current_node = *head;

	while (current_node->next)
	{
		if (!_strcmp(current_node->key, key))
		{
			free(current_node->value);
			current_node->value = _strdup(value);
			freealias(new_node);
			return (0);
		}

		current_node = current_node->next;
	}

	current_node->next = new_node;
	return (0);
}

/**
 * print_lalias - Print the contents of the linked list.
 * @head: Pointer to the first node.
 *
 * Return: 0 on success, -1 on failure.
 */
int print_lalias(alias *head)
{
	if (!head)
		return (-1);

	while (head)
	{
		_write(-1, NULL, 0);
		_write(1, head->key, _strlen(head->key));
		_write(1, "='", 2);
		_write(1, head->value, _strlen(head->value));
		_write(1, "'\n", 2);
		_write(1, NULL, 0);

		head = head->next;
	}

	return (0);
}

/**
 * print_alias - Print the contents of a node whose key matches the given key.
 * @head: Pointer to the first node.
 * @key: Key of the node to be printed.
 *
 * Return: 0 on success, -1 on failure.
 */
int print_alias(alias *head, char *key)
{
	char *msg, *smn;

	if (!head)
	{
		errno = -5;
		msg = _malloc(_strlen("not found ") + _strlen(key) + 4);
		_strcpy(msg, "not found ");
		smn = _malloc(_strlen("alias: ") + _strlen(key) + 4);
		_strcpy(smn, "alias: "), _strcat(smn, key);
		print_error(smn, NULL, msg);
		free(msg), free(smn);
		return (-1);
	}

	while (head)
	{
		if (!_strcmp(head->value, key))
		{
			_write(-1, NULL, 0);
			_write(1, head->key, _strlen(head->key));
			_write(1, "='", 2);
			_write(1, head->value, _strlen(head->value));
			_write(1, "'\n", 2);
			_write(1, NULL, 0);
			return (0);
		}

		head = head->next;
	}

	errno = -3;
	msg = _malloc(_strlen("not found ") + _strlen(key) + 4);
	_strcpy(msg, "not found ");
	smn = _malloc(_strlen("alias: ") + _strlen(key) + 4);
	
#include "shell.h"

/**
 * handle_alias - Handle flags for aliases.
 * @arg: Arguments.
 * @aliashead: Pointer to the first node.
 *
 * Return: 0 on success, -1 on failure.
 */
int handle_alias(char **arg, alias **aliashead)
{
	int argc = _arlen(arg);
	int i = 0;
	char **tmp = NULL;

	if (argc == 0)
		return (-1);

	if (argc == 1)
		print_lalias(*aliashead);

	if (argc > 1)
	{
		i += 1;
		while (arg[i])
		{
			parse_args(arg[i], "=", &tmp, 0);
			if (_arlen(tmp) > 1)
				add_alias(aliashead, tmp[0], tmp[1]);
			else
				print_alias(*aliashead, tmp[0]);
			free_pp(tmp);
			i++;
		}
	}

	return (0);
}

/**
 * freealias - Free the alias linked list.
 * @head: Pointer to the first node.
 *
 * Return: 0 on success, -1 on failure.
 */
int freealias(alias *head)
{
	alias *tmp;

	while (head)
	{
		tmp = head->next;
		free(head->key);
		free(head->value);
		free(head);
		head = tmp;
	}

	return (0);
}
