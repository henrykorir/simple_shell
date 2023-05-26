#include "shell.h"
#define l(x) _strlen((x))
#define cch const char

/**
 * put_environment - write to environment variables
 * @es: environment variable value argument pair
 * Return: 0 on success and -1 on failure
 */

int put_environment(char *es)
{
	char **current_environment = environ;
	char **new_environment, **current_new_environment;
	int len = 0;

	while (*current_environment)
	{
		len++;
		current_environment++;
	}

	new_environment = _malloc(sizeof(char *) * (len + 4));
	current_new_environment = new_environment;
	current_environment = environ;

	while (len)
	{
		*current_new_environment = _malloc(sizeof(char) * _strlen(*current_environment) + 4);
		_strcpy(*current_new_environment, *current_environment);
		current_new_environment++;
		current_environment++;
		len--;
	}

	*current_new_environment = _malloc(sizeof(char) * _strlen(es) + 4);
	_strcpy(*current_new_environment, es);
	free(es);
	current_new_environment++;
	*current_new_environment = NULL;
	free_pp(environ);
	environ = new_environment;
	return (0);
}

/**
 * set_environment - set environment variables
 * @name: variable name
 * @value: value
 * @overwrite: overwrite status
 *
 * Return: 0 on success and -1 on failure
 */

int set_environment(cch *name, cch *value, __attribute__((unused))int overwrite)
{
	char *es, **ep, *var;
	int i = 0;

	if (name == NULL || name[0] == '\0' || value == NULL)
		return (-1);

	if (environ)
	{
		ep = _arrdup(environ);
		while (ep[i])
		{
			var = _strtok(ep[i], "=", 0);
			if (!_strcmp(var, (char *)name))
			{
				free(environ[i]);
				environ[i] = _malloc(_strlen(name) + _strlen(value) + 4);
				_strcpy(environ[i], (char *)name);
				_strcat(environ[i], "=");
				_strcat(environ[i], (char *)value);
				free_pp(ep);
				return (0);
			}
			i++;
		}
		free_pp(ep);
	}

	es = _malloc(_strlen(name) + _strlen(value) + 2);
	if (es == NULL)
		return (-1);
	_strcpy(es, (char *)name), _strcat(es, "="), _strcat(es, (char *)value);
	return ((put_environment(es) != 0) ? -1 : 0);
	free(es);
}

/**
 * unset_environment - delete environment variables
 * @name: name of variable
 * Return: 0 on success and -1 on failure
 */

int unset_environment(const char *name)
{
	char **ep, **sp, *var, *value;

	if (name == NULL || name[0] == '\0')
		return (-1);
	ep = _arrdup(environ);
	free_pp(environ);
	environ = _malloc(sizeof(char *));

	for (sp = ep; *sp != NULL; )
	{
		var = _strtok(*sp, "=", 0);
		if (_strcmp(var, (char *)name))
		{
			value = _strtok(NULL, "=", 0);
			set_environment(var, value, 1);
		}
		sp++;
	}
	free_pp(ep);
	return (0);
}

/**
 * print_environment - print environment variables
 */

void print_environment(void)
{
	char **env = environ;

	if (!env)
		return;

	_write(-1, NULL, 0);

	while (*env)
	{
		write(1, *env, _strlen(*env));
		write(1, "\n", 1);
		env++;
	}

	write(1, NULL, 0);
}

/**
 * get_environment - get environment variables
 * @name: name of variable
 * Return: pointer to environment variables
 */

char *get_environment(const char *name)
{
	int len, i;
	const char *np;
	char **p, *cp;

	if (name == NULL || environ == NULL)
		return (NULL);

	for (np = name; *np && *np != '='; ++np)
		;

	len = np - name;

	for (p = environ; (cp = *p) != NULL; ++p)
	{
		for (np = name, i = len; i && *cp; i--)
		{
			if (*cp++ != *np++)
				break;
		}

		if (i == 0 && *cp++ == '=')
			return (cp);
	}

	return (NULL);
}
