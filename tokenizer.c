#include "shell.h"

/**
 * **strtow - Splits a string into words, ignoring repeated delimiters.
 *
 * @str: The input string.
 * @delim: The delimiter string.
 *
 * Return: A pointer to an array of strings, or NULL on failure.
 */

char **strtow(char *str, char *delim)
{
	int i, j, k, m, num_words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!delim)
		delim = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], delim) && (is_delim(str[i + 1], delim) || !str[i + 1]))
			num_words++;

	if (num_words == 0)
		return (NULL);
	s = malloc((1 + num_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (is_delim(str[i], delim))
			i++;
		k = 0;
		while (!is_delim(str[i + k], delim) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **strtow2 - Splits a string into an array of tokens
 * @str: The input string to be split
 * @delim: The delimiter character used to split the input string
 *
 * Return: A pointer to an array of strings containing the tokens,
 *         or NULL if the function fails.
 */

char **strtow2(char *str, char delim)
{
	int i, j, k, m, num_words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != delim && str[i + 1] == delim) ||
			(str[i] != delim && !str[i + 1]) || str[i + 1] == delim)
			num_words++;
	if (num_words == 0)
		return (NULL);
	s = malloc((1 + num_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (str[i] == delim && str[i] != delim)
			i++;
		k = 0;
		while (str[i + k] != delim && str[i + k] && str[i + k] != delim)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
