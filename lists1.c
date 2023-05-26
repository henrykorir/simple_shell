#include "shell.h"

/**
 * list_len - Calculates the number of nodes in a linked list.
 *
 * @head_ptr: Pointer to the first node in the list.
 *
 * Return: The number of nodes in the linked list.
 */

size_t list_len(const list_t *head_ptr)
{
	size_t count = 0;

	while (head_ptr)
	{
		head_ptr = head_ptr->next;
		count++;
	}
	return (count);
}

/**
 * list_to_strings - Creates an array of strings from the `str` field of a linked list.
 *
 * @head: Pointer to the first node in the list.
 *
 * Return: Array of strings.
 */

char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t size = list_len(head), i, j;
	char **str_array;
	char *str;

	if (!head || !size)
		return (NULL);
	str_array = malloc(sizeof(char *) * (size + 1));
	if (!str_array)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(str_array[j]);
			free(str_array);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		str_array[i] = str;
	}
	str_array[i] = NULL;
	return (str_array);
}

/**
 * print_list - Prints all elements of a linked list of type list_t.
 *
 * @head: Pointer to the first node of the list.
 *
 * Return: Size of the list.
 */

size_t print_list(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		_puts(convert_number(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		count++;
	}
	return (count);
}

/**
 * node_starts_with - finds the first node in the linked list @head whose string
 * begins with the string @prefix followed by the character @c.
 *
 * @head: a pointer to the head of the list.
 * @prefix: the string to match at the beginning of the node's string.
 * @c: the character to match immediately after the prefix.
 *
 * Return: a pointer to the first matching node found, or NULL if no match is found.
 */

list_t *node_starts_with(list_t *head, char *prefix, char c)
{
	char *p = NULL;

	while (head)
	{
		p = starts_with(head->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (head);
		head = head->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node in the linked list @head.
 *
 * @head: a pointer to the head of the list.
 * @node: a pointer to the node whose index is to be retrieved.
 *
 * Return: the index of the node in the list, or -1 if the node is not found.
 */

ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
			return (index);
		head = head->next;
		index++;
	}
	return (-1);
}
