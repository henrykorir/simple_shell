#include "shell.h"

/**
 * my_strncpy - Copies the first n characters of a string.
 *
 * @dest: The destination string to copy to.
 * @src: The source string to be copied.
 * @n: The maximum number of characters to copy.
 *
 * Return: The destination string after copying.
 */

char *my_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *result = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (result);
}

/**
 * my_strncat - Concatenates the first n bytes of the source string to the end of the destination string.
 *
 * @dest: The first string.
 * @src: The second string to concatenate.
 * @n: The maximum number of bytes to be used from src.
 *
 * Return: A pointer to the resulting concatenated string.
 */

char *my_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *result = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (result);
}

/**
 * my_strchr - Locates the first occurrence of a character in a string.
 *
 * @s: The string to search.
 * @c: The character to look for.
 *
 * Return: A pointer to the first occurrence of the character in the string,
 *         or NULL if the character is not found.
 */

char *my_strchr(char *s, char c)
{
	do
	{
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
