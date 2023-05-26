#include "shell.h"

/**
 * expand_command_signs - expand command signs
 * @str: string to be used
 * @status: last exit status
 */
void expand_command_signs(char **str, int status)
{
	char *pid = itoa(getpid()), *stats = itoa(status);

	if (**str != '\n')
		find_and_replace(str, "$$", pid), find_and_replace(str, "$?", stats);

	free(pid), free(stats);
}

/**
 * expand_environment_vars - expand environment variables in string
 * @str: the string
 * Return: none
 */
void expand_environment_vars(char **str)
{
	int i = 0, j = 0;
	char *var, *tmp, *rep;

	while (*(*str + i))
	{
		if (*(*str + i) == '$' && *str + i + 1)
		{
			if (*(*str + i + 1) != '$' && *(*str + i + 1) != '?')
			{
				var = _malloc(2), tmp = NULL;
				j = 0;
				var[0] = 'k', var[1] = '\0';
				while (*(*str + i + j) != ' ' && *(*str + i + j))
				{
					var = _realloc(var, _strlen(var) + 16);
					*(var + j) = *(*str + i + j), *(var + j + 1) = '\0';
					if (!(*str + i + j + 1))
						break;
					j++;
				}
				tmp = _malloc(_strlen(var)), _strcpy(tmp, var + 1);
				rep = getenv(tmp);
				if (rep)
					find_and_replace(str, var, rep);
				else
					find_and_replace(str, var, "");
				free(var), free(tmp);
				var = (char *)_malloc(2), var[0] = ' ', var[1] = '\0', tmp = NULL;
				free(var);
			}
		}
		i++;
	}
}

/**
 * remove_comments - remove characters after the '#' character in string
 * @str: the string
 * Return: none
 */
void remove_comments(char **str)
{
	char *_str = *str;

	while (*_str)
	{
		if (*_str == '#')
		{
			*_str = '\0';
			break;
		}
		_str++;
	}
}

/**
 * expand_shell_vars - expand shell variables
 * @str: string containing variables
 * @child_status: the last exit status of the child process
 *
 * Return: 0 on success and -1 on error
 */
int expand_shell_vars(char **str, int child_status)
{
	expand_command_signs(str, child_status);
	expand_environment_vars(str);
	remove_comments(str);
	return (0);
}

/**
 * expand_aliases - expand aliases inside a string
 * @str: string to be manipulated
 * @head: first node
 */
void expand_aliases(char **str, alias *head)
{
	while (head)
	{
		find_and_replace(str, head->key, head->value);
		head = head->next;
	}
}
