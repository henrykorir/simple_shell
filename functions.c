#include "shell.h"

/**
 * _strcmp - compare two strings
 * @str1: string to compare
 * @str2: string to compare
 * Return: 0 on success, a non-zero value otherwise
 */
int _strcmp(char *str1, char *str2)
{
int i = 0;
int result;

while (str1[i] != '\0' && str2[i] != '\0')
{
if (str1[i] == str2[i])
result = 0;
else
{
result = (str1[i] - '0') - (str2[i] - '0');
return (result);
}
i++;
}

return (result);
}

/**
 * _strcpy - copies the string pointed to by src
 * @dest: where the string will be copied
 * @src: string to copy
 * Return: pointer to the destination string
 */
char *_strcpy(char *dest, char *src)
{
int length = 0;
int i;

while (src[length] != '\0')
length++;

for (i = 0; i <= length; i++)
dest[i] = src[i];

return (dest);
}

/**
 * _strcat - concatenates two strings
 * @dest: main string
 * @src: string to add to dest
 * Return: pointer to the concatenated string
 */
char *_strcat(char *dest, char *src)
{
int i = 0;
int j = 0;

while (dest[i] != '\0')
i++;

while (src[j] != '\0')
{
dest[i] = src[j];
i++;
j++;
}

dest[i] = '\0';
return (dest);
}

/**
 * sp_string - Split a string using strtok function
 * @str: string to be split
 * @delimiters: delimiters for the string
 * Return: a double pointer array with the string splitted
 */
char **sp_string(char *str, char *delimiters)
{
char **tokens;
char *token;
int i = 0;

tokens = (char **)malloc(sizeof(char *) * 1024);
if (tokens == NULL)
{
/* Print error for malloc */
return (NULL);
}

token = strtok(str, delimiters);
while (token != NULL)
{
tokens[i] = token;
token = strtok(NULL, delimiters);
i++;
}

tokens[i] = NULL;
return (tokens);
}
